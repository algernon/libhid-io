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

#define TEST_DATA_MAX 64

typedef struct {
  hidio_io_t parent;

  uint8_t in_data[TEST_DATA_MAX];
  uint8_t out_data[TEST_DATA_MAX];
} test_hidio_io_t;

void test_io_read(hidio_io_t *self, uint8_t *data, uint16_t data_length) {
  test_hidio_io_t *s = (test_hidio_io_t *)self;
  memcpy(data, s->in_data, data_length);
}

void test_io_write(hidio_io_t *self, uint8_t *data, uint16_t data_length) {
  test_hidio_io_t *s = (test_hidio_io_t *)self;
  memcpy(s->out_data, data, data_length);
}

void test_io_setup(test_hidio_io_t *io) {
  io->parent.read = test_io_read;
  io->parent.write = test_io_write;
  memset(io->in_data, 0, sizeof(io->in_data));
  memset(io->out_data, 0, sizeof(io->out_data));
}
