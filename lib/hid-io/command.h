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

#include <hid-io/guards.h>
#include <hid-io/packet.h>
#include <string.h>

HIDIO_CPP_GUARD_START

typedef struct hidio_command_t hidio_command_t;
struct hidio_command_t {
  hidio_packet_id_size_t id;

  void (*process)(hidio_io_t *io, hidio_command_t *command);
  void (*ack)(hidio_io_t *io, hidio_command_t *command, hidio_packet_id_size_t id);
  void (*nak)(hidio_io_t *io, hidio_command_t *command, hidio_packet_id_size_t id);
};

extern hidio_command_t hidio_commands[];

void hidio_command_no_payload_nak(hidio_io_t *io,
                                  hidio_command_t *command,
                                  hidio_packet_id_size_t id);
void hidio_command_process(hidio_io_t *io);

/* --- */
void hidio_command_supported_ids_process(hidio_io_t *io,
                                         hidio_command_t *command);
void hidio_command_supported_ids_ack(hidio_io_t *io,
                                     hidio_command_t *command,
                                     hidio_packet_id_size_t id);

#define HIDIO_COMMAND_SUPPORTED_IDS                                     \
  {0x0000,                                                              \
   hidio_command_supported_ids_process,                                 \
   hidio_command_supported_ids_ack,                                     \
   hidio_command_no_payload_nak}

#define HIDIO_COMMAND_END {0, NULL, NULL, NULL}

HIDIO_CPP_GUARD_END
