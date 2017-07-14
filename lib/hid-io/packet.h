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

#pragma once

#include <stdint.h>

#include <hid-io/guards.h>
#include <hid-io/io.h>

HIDIO_CPP_GUARD_START

typedef enum {
  HIDIO_PACKET_TYPE_DATA,
  HIDIO_PACKET_TYPE_ACK,
  HIDIO_PACKET_TYPE_NAK,
  HIDIO_PACKET_TYPE_SYNC
} hidio_packet_type_t;

typedef struct {
  hidio_packet_type_t type:3;
  uint8_t             is_continued:1; // is this a continued packet?
  uint8_t             is_id_32bit:1;  // is the id 32bit? (16 otherwise)
  uint8_t             reserved:1;
  uint8_t             data_length_upper:2;
  uint8_t             data_length_lower;
} __attribute__((packed)) hidio_packet_header_t;

typedef uint32_t hidio_id_t;

const uint16_t hidio_packet_data_length(const hidio_packet_header_t *packet_header);

void hidio_packet_header_read(hidio_io_t *io, hidio_packet_header_t *packet_header);
void hidio_packet_header_write(hidio_io_t *io, const hidio_packet_header_t *packet_header);

HIDIO_CPP_GUARD_END