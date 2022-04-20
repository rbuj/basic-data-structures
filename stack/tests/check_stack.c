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
#include <signal.h>
#include <limits.h>
#include <check.h>
#include "../src/stack.h"

#define STACK_CAPACITY 10

Stack *stack = NULL;

void
setup (void)
{
  stack = stack_create (STACK_CAPACITY);
}

void
teardown (void)
{
  stack_destroy (&stack);
}

START_TEST (test_stack_create)
{
  ck_assert (stack_is_empty (stack));
  ck_assert (!stack_is_full (stack));

  stack_push (stack, 10);
  ck_assert (!stack_is_empty (stack));
  ck_assert_int_eq (stack_peek (stack), 10);

  stack_push (stack, 20);
  ck_assert_int_eq (stack_peek (stack), 20);

  stack_push (stack, 30);
  ck_assert_int_eq (stack_peek (stack), 30);

  ck_assert (!stack_is_empty (stack));
  ck_assert (!stack_is_full (stack));

  ck_assert_int_eq (stack_pop (stack), 30);
  ck_assert_int_eq (stack_peek (stack), 20);

  ck_assert_int_eq (stack_pop (stack), 20);
  ck_assert_int_eq (stack_peek (stack), 10);

  ck_assert_int_eq (stack_pop (stack), 10);

  ck_assert (stack_is_empty (stack));
}

START_TEST (test_stack_clean)
{
  ck_assert (stack_is_empty (stack));
  stack_push (stack, 10);
  ck_assert (!stack_is_empty (stack));
  stack_clean (stack);
  ck_assert (stack_is_empty (stack));
}

START_TEST (test_stack_clean_empty)
{
  ck_assert (stack_is_empty (stack));
  stack_clean (stack);
  ck_assert (stack_is_empty (stack));
}

START_TEST (test_stack_is_full)
{
  int i;

  ck_assert (stack_is_empty (stack));
  for (i = 0; i < STACK_CAPACITY; i++) {
    ck_assert (!stack_is_full (stack));
    stack_push (stack, i);
  }
  ck_assert (stack_is_full (stack));
}

START_TEST (test_stack_is_full_empty)
{
  ck_assert (stack_is_empty (stack));
  ck_assert (!stack_is_full (stack));
}

START_TEST (test_stack_peek_empty)
{
  ck_assert (stack_is_empty (stack));
  ck_assert (stack_peek (stack) == INT_MIN);
}

START_TEST (test_stack_pop_empty)
{
  ck_assert (stack_is_empty (stack));
  ck_assert (stack_pop (stack) == INT_MIN);
}

/* tc_null_check */

START_TEST (test_stack_destroy_null)
{
  ck_assert (stack == NULL);
  stack_destroy (&stack);
}

START_TEST (test_stack_clean_null)
{
  ck_assert (stack == NULL);
  stack_clean (stack);
}
START_TEST (test_stack_is_empty_null)
{
  ck_assert (stack == NULL);
  stack_is_empty (stack);
}

START_TEST (test_stack_is_full_null)
{
  ck_assert (stack == NULL);
  stack_is_full (stack);
}

START_TEST (test_stack_peek_null)
{
  ck_assert (stack == NULL);
  (void) stack_peek (stack);
}

START_TEST (test_stack_pop_null)
{
  ck_assert (stack == NULL);
  (void) stack_pop (stack);
}

START_TEST (test_stack_push_null)
{
  ck_assert (stack == NULL);
  stack_push (stack, 1);
}

Suite *
check_stack_suite (void)
{
  Suite *s;
  TCase *tc_core;
  TCase *tc_null_check;

  s = suite_create ("Stack");

  tc_core = tcase_create ("Core");
  tcase_add_checked_fixture (tc_core, setup, teardown);
  tcase_add_test (tc_core, test_stack_create);
  tcase_add_test (tc_core, test_stack_clean);
  tcase_add_test (tc_core, test_stack_clean_empty);
  tcase_add_test (tc_core, test_stack_is_full);
  tcase_add_test (tc_core, test_stack_is_full_empty);
  tcase_add_test (tc_core, test_stack_peek_empty);
  tcase_add_test (tc_core, test_stack_pop_empty);
  suite_add_tcase (s, tc_core);

  tc_null_check = tcase_create("Null");
  tcase_add_test              (tc_null_check, test_stack_destroy_null);
  tcase_add_test_raise_signal (tc_null_check, test_stack_clean_null, SIGABRT);
  tcase_add_test_raise_signal (tc_null_check, test_stack_is_empty_null, SIGABRT);
  tcase_add_test_raise_signal (tc_null_check, test_stack_is_full_null, SIGABRT);
  tcase_add_test_raise_signal (tc_null_check, test_stack_peek_null, SIGABRT);
  tcase_add_test_raise_signal (tc_null_check, test_stack_pop_null, SIGABRT);
  tcase_add_test_raise_signal (tc_null_check, test_stack_push_null, SIGABRT);
  suite_add_tcase (s, tc_null_check);

  return s;
}

int
main (void)
{
  int      number_failed;
  Suite   *s;
  SRunner *sr;

  s = check_stack_suite ();
  sr = srunner_create (s);

  srunner_run_all (sr, CK_NORMAL);
  number_failed = srunner_ntests_failed (sr);
  srunner_free (sr);
  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
