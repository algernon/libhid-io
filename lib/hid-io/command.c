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

void hidio_command_data_prepare(hidio_packet_id_t id, const uint8_t *data, uint16_t data_length) {
  hidio_packet_type_set(HIDIO_PACKET_TYPE_DATA);
  hidio_packet_id_set(id);
  hidio_packet_continued_set(0);
  hidio_packet_data_length_set(data_length);
  if (data_length)
    hidio_packet_data_set(data);
}

void hidio_command_no_payload_nak(hidio_io_t *io,
                                  hidio_command_t *command,
                                  hidio_packet_id_t id) {
  hidio_packet_type_set(HIDIO_PACKET_TYPE_NAK);
  hidio_packet_id_set(id);
  hidio_packet_continued_set(0);
  hidio_packet_data_length_set(0);
  hidio_packet_send(io);
}

void hidio_command_process(hidio_io_t *io) {
  hidio_packet_id_t id = hidio_packet_id();

  for (uint8_t i = 0; hidio_commands[i].process != NULL; i++) {
    if (hidio_commands[i].id == id) {
      return hidio_commands[i].process(io, &hidio_commands[i]);
    }
  }

  return hidio_command_no_payload_nak(io, NULL, id);
}

/* --- 0x00 supported ids --- */

void hidio_command_supported_ids_process(hidio_io_t *io,
                                         hidio_command_t *command) {
  command->ack(io, command, 0x0000);
}

void hidio_command_supported_ids_ack(hidio_io_t *io,
                                     hidio_command_t *command,
                                     hidio_packet_id_t id) {
  uint8_t finished = 0;

  hidio_packet_type_set(HIDIO_PACKET_TYPE_ACK);
  hidio_packet_id_set(0);
  hidio_packet_continued_set(0);
  hidio_packet_data_length_set(0);

  for (uint8_t i = 0; hidio_commands[i].process != NULL; i++) {
    if (hidio_packet_data_append((uint8_t *)&hidio_commands[i].id, sizeof(hidio_packet_id_t)) == 0) {
      finished = 0;
      continue;
    }

    hidio_packet_continued_set(1);
    hidio_packet_send(io);

    hidio_packet_continued_set(0);
    hidio_packet_data_length_set(0);
    finished = 1;
  }

  if (!finished) {
    hidio_packet_send(io);
  }
}

/* --- 0x01 get info --- */
void hidio_command_get_info_process(hidio_io_t *io,
                                    hidio_command_t *command) {
  uint8_t property = hidio_packet_data()[0];

  switch (property) {
  case 0x00 ... 0x05:
    command->ack(io, command, 0x0001);
    break;
  default:
    command->nak(io, command, 0x0001);
    break;
  }
}

void hidio_command_get_info_ack(hidio_io_t *io,
                                hidio_command_t *command,
                                hidio_packet_id_t id) {
  uint8_t property = hidio_packet_data()[0];

  hidio_packet_type_set(HIDIO_PACKET_TYPE_ACK);
  hidio_packet_id_set(0x01);
  hidio_packet_continued_set(0);

  switch (property) {
  case 0x00 ... 0x02:
    {
      uint16_t v;

      hidio_packet_data_length_set(sizeof(uint16_t));

      switch (property) {
      case 0x00:
        v = HIDIO_PROTOCOL_VERSION_MAJOR;
        break;
      case 0x01:
        v = HIDIO_PROTOCOL_VERSION_MINOR;
        break;
      case 0x02:
        v = HIDIO_PROTOCOL_VERSION_PATCH;
        break;
      }
      hidio_packet_data_set((uint8_t *)&v);

      break;
    }
  case 0x03:
    {
      static const char *device_name = "test-device";

      hidio_packet_data_length_set(strlen(device_name));
      hidio_packet_data_set(device_name);
      break;
    }
  }

  hidio_packet_send(io);
}

void hidio_command_get_info_nak(hidio_io_t *io,
                                hidio_command_t *command,
                                hidio_packet_id_t id) {
  hidio_command_no_payload_nak(io, NULL, id);
}
