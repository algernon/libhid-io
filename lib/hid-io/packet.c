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

const uint16_t hidio_packet_data_length(const hidio_packet_t *packet) {
  return packet->header.data_length_upper * 256 + packet->header.data_length_lower;
}

const uint8_t *hidio_packet_data(const hidio_packet_t *packet) {
  if (packet->header.is_id_32bit) {
    return &packet->data_id32.data[0];
  } else {
    return &packet->data_id16.data[0];
  }
}

const uint32_t hidio_packet_id(const hidio_packet_t *packet) {
  if (packet->header.is_id_32bit) {
    return packet->data_id32.id;
  } else {
    return packet->data_id16.id;
  }
}

int8_t hidio_packet_read(hidio_io_t *io, hidio_packet_t *packet) {
  io->read(io, (uint8_t *)packet, sizeof(hidio_packet_t));
}

int8_t hidio_packet_write(hidio_io_t *io, const hidio_packet_t *packet) {
  io->write(io, (uint8_t *)packet, sizeof(hidio_packet_t));
}
