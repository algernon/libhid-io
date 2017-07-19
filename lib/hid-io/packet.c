/* hid-io -- HID-IO firmware & host support library
 * Copyright (C) 2017  Gergely Nagy
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <hid-io/hid-io.h>
#include <string.h>

typedef union hidio_packet_t {
  struct {
    struct {
      hidio_packet_type_t type:3;
      uint8_t             is_continued:1; // is this a continued packet?
      uint8_t             is_id_32bit:1;  // is the id 32bit? (16 otherwise)
      uint8_t             reserved:1;
      uint8_t             data_length_upper:2;
      uint8_t             data_length_lower;
    } __attribute__((packed)) header;

    union {
      struct {
        uint8_t data[0];
      } __attribute__((packed)) data_id0;
      struct {
        uint16_t id;
        uint8_t data[0];
      } __attribute__((packed)) data_id16;
      struct {
        uint32_t id;
        uint8_t data[0];
      } __attribute__((packed)) data_id32;
    } __attribute__((packed));
  } __attribute__((packed));
  uint8_t raw[64];
} __attribute__((packed)) hidio_packet_t;

static hidio_packet_t incoming_packet, outgoing_packet;

const uint16_t hidio_packet_data_length_max(void) {
  return sizeof(hidio_packet_t) -
    (sizeof(incoming_packet.header) +
     sizeof(incoming_packet.data_id32.id));
}

hidio_packet_type_t hidio_packet_type(void) {
  return incoming_packet.header.type;
}

void hidio_packet_type_set(hidio_packet_type_t type) {
  outgoing_packet.header.type = type;
}

const uint16_t __packet_size(hidio_packet_t *packet) {
  return packet->header.data_length_upper * 256 +
    packet->header.data_length_lower;
}

uint16_t hidio_packet_data_length(void) {
  return __packet_size(&incoming_packet);
}

int8_t hidio_packet_data_length_set(const uint16_t length) {
  if (length >= 256 * 4)
    return -1;

  if (length >= 256) {
    outgoing_packet.header.data_length_upper = length / 256;
    outgoing_packet.header.data_length_lower = length % 256;
  } else {
    outgoing_packet.header.data_length_upper = 0;
    outgoing_packet.header.data_length_lower = length;
  }

  return 0;
}

const uint8_t *hidio_packet_data(void) {
  if (incoming_packet.header.is_id_32bit) {
    return &incoming_packet.data_id32.data[0];
  } else {
    return &incoming_packet.data_id16.data[0];
  }
}

int8_t hidio_packet_data_set(const uint8_t *data) {
  if (outgoing_packet.header.is_id_32bit) {
    memcpy(&outgoing_packet.data_id32.data[0], data,
           __packet_size(&outgoing_packet));
  } else {
    memcpy(&outgoing_packet.data_id16.data[0], data,
           __packet_size(&outgoing_packet));
  }
  return 0;
}

hidio_packet_id_t hidio_packet_id(void) {
  if (incoming_packet.header.is_id_32bit)
    return (hidio_packet_id_t)incoming_packet.data_id32.id;
  else
    return (hidio_packet_id_t)incoming_packet.data_id16.id;
}

int8_t hidio_packet_id_set(const hidio_packet_id_t id) {
#if SIZEOF_VOID_P > 2
  if (id > 65535) {
    outgoing_packet.header.is_id_32bit = 1;
    outgoing_packet.data_id32.id = id;
  } else {
    outgoing_packet.header.is_id_32bit = 0;
    outgoing_packet.data_id16.id = id;
  }
#else
  outgoing_packet.header.is_id_32bit = 0;
  outgoing_packet.data_id16.id = id;
#endif

  return 0;
}

uint8_t hidio_packet_is_continued(void) {
  return incoming_packet.header.is_continued;
}

void hidio_packet_continued_set(const uint8_t is_continued) {
  outgoing_packet.header.is_continued = is_continued;
}

int8_t hidio_packet_recv(hidio_io_t *io) {
  uint8_t offset = sizeof(incoming_packet.header);

  // Read the header
  io->read(io, (uint8_t *)&incoming_packet.header, sizeof(incoming_packet.header));
  // Read the id
  if (incoming_packet.header.is_id_32bit) {
    offset += sizeof(incoming_packet.data_id32.id);
    io->read(io, (uint8_t *)&incoming_packet.data_id32.id, sizeof(incoming_packet.data_id32.id));
  } else {
    offset += sizeof(incoming_packet.data_id16.id);
    io->read(io, (uint8_t *)&incoming_packet.data_id16.id, sizeof(incoming_packet.data_id16.id));
  }

  // Read the payload
  io->read(io, (uint8_t *)&incoming_packet.raw[offset], __packet_size(&incoming_packet));
}

int8_t hidio_packet_send(hidio_io_t *io) {
  uint8_t size = sizeof(outgoing_packet.header) + __packet_size(&outgoing_packet);

  if (outgoing_packet.header.is_id_32bit) {
    size += sizeof(outgoing_packet.data_id32.id);
  } else {
    size += sizeof(outgoing_packet.data_id16.id);
  }

  io->write(io, (uint8_t *)&outgoing_packet.raw, size);
}

void hidio_packet_swap(void) {
  hidio_packet_t tmp;

  memcpy(&tmp, &incoming_packet, sizeof(tmp));
  memcpy(&incoming_packet, &outgoing_packet, sizeof(incoming_packet));
  memcpy(&outgoing_packet, &tmp, sizeof(outgoing_packet));
}

void hidio_packet_reset(void) {
  memset(&incoming_packet, 0, sizeof(incoming_packet));
  memset(&outgoing_packet, 0, sizeof(outgoing_packet));
}
