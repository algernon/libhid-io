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

const hidio_packet_t *hidio_command_supported_ids_response_create(hidio_io_t *io, const hidio_packet_t *in_packet) {
  static hidio_packet_t r;

  r.header.type = HIDIO_PACKET_TYPE_ACK;
  r.header.is_continued = 0;
  r.header.is_id_32bit = 0;
  r.header.reserved = 0;
  r.header.data_length_upper = 0;
  r.header.data_length_lower = 1;
  r.data_id16.id = 0;
  r.data_id16.data[0] = 0;

  return &r;
}

const uint8_t *hidio_command_supported_ids_list_from_response(const hidio_packet_t *response) {
  return hidio_packet_data(response);
}
