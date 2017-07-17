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

START_TEST(test_hidio_packet_data) {
  uint8_t test_data[16];

  memset(test_data, 42, sizeof(test_data));
  hidio_packet_type_set(HIDIO_PACKET_TYPE_ACK);
  hidio_packet_id_set(72000);
  hidio_packet_data_length_set(sizeof(test_data));
  hidio_packet_data_set(test_data);

  hidio_packet_swap();

  ck_assert(hidio_packet_type() == HIDIO_PACKET_TYPE_ACK);
  ck_assert_uint_eq(hidio_packet_id(), 72000);
  ck_assert_uint_eq(hidio_packet_data_length(), sizeof(test_data));
  ck_assert(memcmp(hidio_packet_data(), test_data, sizeof(test_data)) == 0);
}
END_TEST

static TCase *test_hidio_packet (void)
{
  TCase *tests;

  tests = tcase_create ("Packets");
  tcase_add_test (tests, test_hidio_packet_data);

  return tests;
}
