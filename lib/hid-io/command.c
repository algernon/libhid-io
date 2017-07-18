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

void hidio_command_no_payload_nak(hidio_io_t *io,
                                  hidio_command_t *command,
                                  hidio_packet_id_size_t id) {
  hidio_packet_type_set(HIDIO_PACKET_TYPE_NAK);
  hidio_packet_id_set(id);
  hidio_packet_continued_set(0);
  hidio_packet_data_length_set(0);
  hidio_packet_send(io);
}

void hidio_command_process(hidio_io_t *io) {
  hidio_packet_id_size_t id = hidio_packet_id();

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
                                     hidio_packet_id_size_t id) {
  uint8_t finished = 0;

  hidio_packet_type_set(HIDIO_PACKET_TYPE_ACK);
  hidio_packet_id_set(0);
  hidio_packet_continued_set(1);

  for (uint8_t i = 0; hidio_commands[i].process != NULL; i++) {
    if (hidio_commands[i + 1].process == NULL)
      hidio_packet_continued_set(0);
    hidio_packet_data_length_set(sizeof(hidio_packet_id_size_t));
    hidio_packet_data_set((uint8_t *)&hidio_commands[i].id);
    hidio_packet_send(io);
  }
}
