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

#include <hid-io/hid-io.h>
#include <check.h>
#include <stdlib.h>

#include "tests.c"
#include "check_io.c"
#include "check_packet.c"
#include "check_command.c"

int main(void) {
  Suite *suite;
  SRunner *runner;

  int nfailed;

  suite = suite_create ("hid-io library tests");

  suite_add_tcase (suite, test_hidio_io());
  suite_add_tcase (suite, test_hidio_packet());
  suite_add_tcase (suite, test_hidio_command());

  runner = srunner_create (suite);

  srunner_run_all (runner, CK_ENV);
  nfailed = srunner_ntests_failed (runner);
  srunner_free (runner);

  return (nfailed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
