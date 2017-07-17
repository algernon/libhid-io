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

// TODO: Implement package splitting

void hidio_command_supported_ids_ack(hidio_io_t *io, uint8_t n, uint8_t ids[]) {
  hidio_packet_type_set(HIDIO_PACKET_TYPE_ACK);
  hidio_packet_continued_set(0);
  hidio_packet_id_set(0);
  hidio_packet_data_length_set(n);
  hidio_packet_data_set(ids);

  hidio_packet_send(io);
}

const uint8_t *hidio_command_supported_ids_list_get(void) {
  return hidio_packet_data();
}
