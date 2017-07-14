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

START_TEST(test_hidio_command_process_supported_ids) {
  hidio_packet_t in_packet;
  const hidio_packet_t *out_packet;
  test_hidio_io_t io;
  const uint8_t *ids;

  test_io_setup(&io);

  out_packet = hidio_command_supported_ids_response_create(&io.parent, &in_packet);
  ck_assert(out_packet != NULL);
  ck_assert_uint_eq(hidio_packet_data_length(out_packet), 1);

  ids = hidio_command_supported_ids_list_from_response(out_packet);
  ck_assert (ids != NULL);
  ck_assert_uint_eq(ids[0], 0);
}
END_TEST

static TCase *test_hidio_command (void)
{
  TCase *tests;

  tests = tcase_create ("Commands");
  tcase_add_test (tests, test_hidio_command_process_supported_ids);

  return tests;
}
