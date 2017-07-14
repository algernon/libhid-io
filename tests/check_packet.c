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

START_TEST(test_hidio_packet_data_length)
{
  hidio_packet_header_t packet_header;

  memset(&packet_header, 0, sizeof(packet_header));

  packet_header.data_length_lower = 128;
  ck_assert_uint_eq(hidio_packet_data_length(&packet_header), 128);

  packet_header.data_length_upper = 1;
  ck_assert_uint_eq(hidio_packet_data_length(&packet_header), 384);
}
END_TEST

START_TEST(test_hidio_packet_header_io) {
  hidio_packet_header_t w_header, r_header;
  test_hidio_io_t io;

  w_header.type = HIDIO_PACKET_TYPE_DATA;
  w_header.is_continued = 0;
  w_header.is_id_32bit = 0;
  w_header.reserved = 0;
  w_header.data_length_upper = 0;
  w_header.data_length_lower = 16;

  test_io_setup(&io);

  hidio_packet_header_write(&io.parent, &w_header);
  ck_assert(memcmp(io.data, &w_header, sizeof(w_header)) == 0);

  memset(&r_header, 0, sizeof(r_header));

  hidio_packet_header_read(&io.parent, &r_header);
  ck_assert(memcmp(&r_header, &w_header, sizeof(r_header)) == 0);
}
END_TEST

static TCase *test_hidio_packet (void)
{
  TCase *tests;

  tests = tcase_create ("Packets");
  tcase_add_test (tests, test_hidio_packet_data_length);
  tcase_add_test (tests, test_hidio_packet_header_io);

  return tests;
}
