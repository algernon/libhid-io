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

#define TEST_DATA_MAX 1024

typedef struct {
  hidio_io_t parent;

  uint8_t data[TEST_DATA_MAX];
} test_hidio_io_t;

void test_io_read(hidio_io_t *self, uint8_t *data, uint16_t data_length) {
  test_hidio_io_t *s = (test_hidio_io_t *)self;
  memcpy(data, s->data, data_length);
}

void test_io_write(hidio_io_t *self, uint8_t *data, uint16_t data_length) {
  test_hidio_io_t *s = (test_hidio_io_t *)self;
  memcpy(s->data, data, data_length);
}

void test_io_setup(test_hidio_io_t *io) {
  io->parent.read = test_io_read;
  io->parent.write = test_io_write;
  memset(io->data, 0, sizeof(io->data));
}

START_TEST(test_hidio_io_basics) {
  test_hidio_io_t io;
  uint8_t test_data[16];

  test_io_setup(&io);
  memset(test_data, 42, sizeof(test_data));

  io.parent.write(&io.parent, test_data, sizeof(test_data));
  ck_assert (memcmp (io.data, test_data, sizeof(test_data)) == 0);
  ck_assert (io.data[sizeof(test_data)] == 0);

  memset(test_data, 0, sizeof(test_data));

  io.parent.read(&io.parent, test_data, sizeof(test_data));
  ck_assert (memcmp (io.data, test_data, sizeof(test_data)) == 0);
}
END_TEST

static TCase *test_hidio_io (void)
{
  TCase *tests;

  tests = tcase_create ("Low-level IO");
  tcase_add_test (tests, test_hidio_io_basics);

  return tests;
}
