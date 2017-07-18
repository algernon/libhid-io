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
#include <hid-io/platform.h>

HIDIO_CPP_GUARD_START

#if SIZEOF_VOID_P == 1
#define hidio_packet_id_size_t uint8_t
#endif

#if SIZEOF_VOID_P == 2
#define hidio_packet_id_size_t uint16_t
#endif

#if SIZEOF_VOID_P >= 4
#define hidio_packet_id_size_t uint32_t
#endif

typedef enum {
  HIDIO_PACKET_TYPE_DATA,
  HIDIO_PACKET_TYPE_ACK,
  HIDIO_PACKET_TYPE_NAK,
  HIDIO_PACKET_TYPE_SYNC
} hidio_packet_type_t;

typedef union hidio_packet_t hidio_packet_t;

hidio_packet_type_t hidio_packet_type(void);
void hidio_packet_type_set(hidio_packet_type_t type);

uint16_t hidio_packet_data_length(void);
const uint16_t hidio_packet_data_length_max(void);
int8_t hidio_packet_data_length_set(const uint16_t length);

const uint8_t *hidio_packet_data(void);
int8_t hidio_packet_data_set(const uint8_t *data);

hidio_packet_id_size_t hidio_packet_id(void);
int8_t hidio_packet_id_set(const hidio_packet_id_size_t id);

uint8_t hidio_packet_is_continued(void);
void hidio_packet_continued_set(const uint8_t is_continued);

int8_t hidio_packet_recv(hidio_io_t *io);
int8_t hidio_packet_send(hidio_io_t *io);

void hidio_packet_swap(void);
void hidio_packet_reset(void);

HIDIO_CPP_GUARD_END
