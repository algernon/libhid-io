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

const uint16_t hidio_packet_data_length(const hidio_packet_header_t *packet_header) {
  return packet_header->data_length_upper * 256 + packet_header->data_length_lower;
}

void hidio_packet_header_read(hidio_io_t *io, hidio_packet_header_t *packet_header) {
  io->read(io, (uint8_t *)packet_header, sizeof(hidio_packet_header_t));
}

void hidio_packet_header_write(hidio_io_t *io, const hidio_packet_header_t *packet_header) {
  io->write(io, (uint8_t *)packet_header, sizeof(hidio_packet_header_t));
}
