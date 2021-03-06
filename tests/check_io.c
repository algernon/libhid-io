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

START_TEST(test_hidio_io_basics) {
  test_hidio_io_t io;
  uint8_t test_data[16];

  test_io_setup(&io);
  memset(test_data, 42, sizeof(test_data));

  io.parent.write(&io.parent, test_data, sizeof(test_data));
  ck_assert (memcmp (io.out_data, test_data, sizeof(test_data)) == 0);
  ck_assert (io.out_data[sizeof(test_data)] == 0);

  memset(test_data, 0, sizeof(test_data));
  memcpy(io.in_data, io.out_data, sizeof(test_data));

  io.parent.read(&io.parent, test_data, sizeof(test_data));
  ck_assert (memcmp (io.in_data, test_data, sizeof(test_data)) == 0);
}
END_TEST

static TCase *test_hidio_io (void)
{
  TCase *tests;

  tests = tcase_create ("Low-level IO");
  tcase_add_test (tests, test_hidio_io_basics);

  return tests;
}
