/* Copyright (C) 2022 Robert Buj <robert.buj@gmail.com>
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
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 * Author: Robert Buj <robert.buj@gmail.com>
 */

#include <stdlib.h>
#include <check.h>
#include "../src/stack.h"

Stack *stack = NULL;

void
setup (void)
{
  create (&stack, 3);
}

void
teardown (void)
{
  destroy (&stack);
}

START_TEST(test_stack_create)
{
  ck_assert (is_empty (stack));
  ck_assert (!is_full (stack));

  push (stack, 10);
  ck_assert (!is_empty (stack));
  ck_assert_int_eq (peek (stack), 10);

  push (stack, 20);
  ck_assert_int_eq (peek (stack), 20);

  push (stack, 30);
  ck_assert_int_eq (peek (stack), 30);

  ck_assert (is_full (stack));

  ck_assert_int_eq (pop (stack), 30);
  ck_assert_int_eq (peek (stack), 20);

  ck_assert_int_eq (pop (stack), 20);
  ck_assert_int_eq (peek (stack), 10);

  ck_assert_int_eq (pop (stack), 10);

  ck_assert (is_empty (stack));
}

Suite *
stack_suite (void)
{
  Suite *s;
  TCase *tc_core;

  s = suite_create ("Stack");
  tc_core = tcase_create ("Core");
  tcase_add_checked_fixture (tc_core, setup, teardown);
  tcase_add_test (tc_core, test_stack_create);
  suite_add_tcase (s, tc_core);
  return s;
}

int
main (void)
{
  int number_failed;
  Suite *s;
  SRunner *sr;

  s = stack_suite ();
  sr = srunner_create (s);

  srunner_run_all (sr, CK_NORMAL);
  number_failed = srunner_ntests_failed (sr);
  srunner_free (sr);
  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
