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

START_TEST(test_hidio_packet_data_length) {
  hidio_packet_t packet;

  memset(&packet, 0, sizeof(packet));

  packet.header.data_length_lower = 128;
  ck_assert_uint_eq(hidio_packet_data_length(&packet), 128);

  packet.header.data_length_upper = 1;
  ck_assert_uint_eq(hidio_packet_data_length(&packet), 384);
}
END_TEST

START_TEST(test_hidio_packet_io) {
  hidio_packet_t w, r;
  test_hidio_io_t io;

  w.header.type = HIDIO_PACKET_TYPE_DATA;
  w.header.is_continued = 0;
  w.header.is_id_32bit = 0;
  w.header.reserved = 0;
  w.header.data_length_upper = 0;
  w.header.data_length_lower = 16;

  test_io_setup(&io);

  hidio_packet_write(&io.parent, &w);
  ck_assert(memcmp(io.out_data, &w, sizeof(w)) == 0);

  memcpy(io.in_data, io.out_data, sizeof(r));

  hidio_packet_read(&io.parent, &r);
  ck_assert(memcmp(&r, &w, sizeof(r)) == 0);
}
END_TEST

START_TEST(test_hidio_packet_id) {
  hidio_packet_t p;

  p.header.is_id_32bit = 0;
  p.data_id16.id = 1024;

  ck_assert_uint_eq(hidio_packet_id(&p), 1024);

  p.header.is_id_32bit = 1;
  p.data_id32.id = 65538;

  ck_assert_uint_eq(hidio_packet_id(&p), 65538);
}
END_TEST

static TCase *test_hidio_packet (void)
{
  TCase *tests;

  tests = tcase_create ("Packets");
  tcase_add_test (tests, test_hidio_packet_data_length);
  tcase_add_test (tests, test_hidio_packet_io);
  tcase_add_test (tests, test_hidio_packet_id);

  return tests;
}
