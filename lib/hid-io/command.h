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

HIDIO_CPP_GUARD_START

void hidio_command_supported_ids_ack(hidio_io_t *io, uint8_t n, uint8_t ids[]);
const uint8_t *hidio_command_supported_ids_list_get(void);

HIDIO_CPP_GUARD_END
