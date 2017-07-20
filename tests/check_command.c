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

hidio_command_t hidio_commands[] = {
  HIDIO_COMMAND_SUPPORTED_IDS,
  HIDIO_COMMAND_GET_INFO,
  HIDIO_COMMAND_END
};

START_TEST(test_hidio_command_supported_ids_ack) {
  test_hidio_io_t io;
  const hidio_packet_id_t *ids;

  hidio_packet_reset();

  test_io_setup(&io);
  hidio_command_supported_ids_ack(&io.parent, NULL, HIDIO_ID_SUPPORTED_IDS);

  test_io_swap(&io);

  hidio_packet_recv(&io.parent);

  ck_assert(hidio_packet_type() == HIDIO_PACKET_TYPE_ACK);
  ck_assert(hidio_packet_id() == HIDIO_ID_SUPPORTED_IDS);
  ck_assert_uint_eq(hidio_packet_data_length(), sizeof(hidio_packet_id_t) * 2);
  ids = (hidio_packet_id_t *)hidio_packet_data();
  ck_assert_uint_eq(ids[0], HIDIO_ID_SUPPORTED_IDS);
  ck_assert_uint_eq(ids[1], HIDIO_ID_GET_INFO);
  ck_assert(hidio_packet_is_continued() == 0);
}
END_TEST

START_TEST(test_hidio_command_get_info) {
  test_hidio_io_t io;
  uint16_t v;
  uint8_t property;
  const char *device;

  test_io_setup(&io);

  hidio_packet_reset();

  property = 0;
  hidio_command_data_prepare(HIDIO_ID_GET_INFO, &property, sizeof(property));
  hidio_packet_swap();

  hidio_command_get_info_ack(&io.parent, NULL, HIDIO_ID_GET_INFO);

  test_io_swap(&io);

  hidio_packet_recv(&io.parent);

  ck_assert(hidio_packet_type() == HIDIO_PACKET_TYPE_ACK);
  ck_assert(hidio_packet_id() == HIDIO_ID_GET_INFO);
  v = ((uint16_t *)hidio_packet_data())[0];
  ck_assert_uint_eq(v, HIDIO_PROTOCOL_VERSION_MAJOR);

  /* --- */
  test_io_setup(&io);
  hidio_packet_reset();

  property = 3;
  hidio_command_data_prepare(HIDIO_ID_GET_INFO, &property, sizeof(property));
  hidio_packet_swap();

  hidio_command_get_info_ack(&io.parent, NULL, HIDIO_ID_GET_INFO);

  test_io_swap(&io);

  hidio_packet_recv(&io.parent);

  ck_assert(hidio_packet_type() == HIDIO_PACKET_TYPE_ACK);
  ck_assert(hidio_packet_id() == HIDIO_ID_GET_INFO);
  device = (const char *)hidio_packet_data();
  ck_assert_str_eq(device, "test-device");
}
END_TEST

static TCase *test_hidio_command (void)
{
  TCase *tests;

  tests = tcase_create ("Commands");
  tcase_add_test (tests, test_hidio_command_supported_ids_ack);
  tcase_add_test (tests, test_hidio_command_get_info);

  return tests;
}
