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
#include <limits.h>
#include <signal.h>
#include <check.h>

#include "../src/list.h"

List *list = NULL;

void
setup (void)
{
  list = list_create ();
}

void
teardown (void)
{
  list_destroy (&list);
}

START_TEST (test_list)
{
  ck_assert (list_is_empty (list));

  list_insert_at_end (list, 20);
  ck_assert (!list_is_empty (list));

  list_insert_at_beginning (list, 10);

  ck_assert_int_eq (list_remove_first (list), 10);
  ck_assert_int_eq (list_remove_first (list), 20);
  ck_assert (list_is_empty (list));
}

START_TEST (test_list_find_empty)
{
  ck_assert (list_is_empty (list));
  ck_assert_int_eq (list_find (list, 0), INT_MIN);
}

START_TEST (test_list_get_empty)
{
  ck_assert (list_is_empty (list));
  (void) list_get (list, 0);
}

START_TEST (test_list_insert_at_negative_index)
{
  ck_assert (list_is_empty (list));
  list_insert_at (list, -1, 1);
}

START_TEST (test_list_insert_at_out_of_bounds)
{
  ck_assert (list_is_empty (list));
  list_insert_at (list, 1, 1);
}

START_TEST (test_list_insert_at_zero_index)
{
  ck_assert (list_is_empty (list));
  list_insert_at (list, 0, 1);
  ck_assert_int_eq (list_get (list, 0), 1);
}

START_TEST (test_list_insert_at_zero_index_empty)
{
  ck_assert (list_is_empty (list));
  list_insert_at (list, 0, 2);
  ck_assert_int_eq (list_get (list, 0), 2);
  list_insert_at (list, 0, 1);
  ck_assert_int_eq (list_get (list, 0), 1);
}

START_TEST (test_list_is_empty)
{
  ck_assert (list_is_empty (list));
  list_insert_at_end (list, 20);
  ck_assert (!list_is_empty (list));
}

START_TEST (test_list_remove_at_empty)
{
  ck_assert (list_is_empty (list));
  (void) list_remove_at (list, 0);
}

START_TEST (test_list_remove_at_negative_index)
{
  ck_assert (list_is_empty (list));
  (void) list_remove_at (list, -1);
}

START_TEST (test_list_remove_first_empty)
{
  ck_assert (list_is_empty (list));
  (void) list_remove_first (list);
}

START_TEST (test_list_remove_last_empty)
{
  ck_assert (list_is_empty (list));
  (void) list_remove_last (list);
}

START_TEST (test_list_set_empty)
{
  ck_assert (list_is_empty (list));
  list_set (list, 0, 1);
}

START_TEST (test_list_set_negative_index)
{
  ck_assert (list_is_empty (list));
  list_set (list, -1, 1);
}

START_TEST (test_list_out_of_bounds)
{
  ck_assert (list_is_empty (list));
  list_set (list, 1, 1);
}

/* tc_null_check */

START_TEST (test_list_destroy_null)
{
  ck_assert (list == NULL);
  list_destroy (&list);
}

START_TEST (test_list_insert_at_beginning_null)
{
  ck_assert (list == NULL);
  list_insert_at_beginning (list, 1);
}

START_TEST (test_list_insert_at_end_null)
{
  ck_assert (list == NULL);
  list_insert_at_end (list, 1);
}

START_TEST (test_list_insert_at_null)
{
  ck_assert (list == NULL);
  list_insert_at (list, 0, 1);
}

START_TEST (test_list_is_empty_null)
{
  ck_assert (list == NULL);
  list_is_empty (list);
}

START_TEST (test_list_remove_at_null)
{
  ck_assert (list == NULL);
  (void) list_remove_at (list, 0);
}


START_TEST (test_list_remove_first_null)
{
  ck_assert (list == NULL);
  (void) list_remove_first (list);
}

START_TEST (test_list_remove_last_null)
{
  ck_assert (list == NULL);
  (void) list_remove_last (list);
}

START_TEST (test_list_set_null)
{
  ck_assert (list == NULL);
  list_set (list, 0, 1);
}

START_TEST (test_list_size_null)
{
  ck_assert (list == NULL);
  list_size (list);
}

Suite *
check_list_suite (void)
{
  Suite *s;
  TCase *tc_core;
  TCase *tc_null_check;

  s = suite_create ("Queue");

  tc_core = tcase_create ("Core");
  tcase_add_checked_fixture   (tc_core, setup, teardown);
  tcase_add_test              (tc_core, test_list);
  tcase_add_test              (tc_core, test_list_find_empty);
  tcase_add_test              (tc_core, test_list_insert_at_zero_index);
  tcase_add_test              (tc_core, test_list_insert_at_zero_index_empty);
  tcase_add_test_raise_signal (tc_core, test_list_get_empty, SIGABRT);
  tcase_add_test_raise_signal (tc_core, test_list_insert_at_negative_index, SIGABRT);
  tcase_add_test_raise_signal (tc_core, test_list_insert_at_out_of_bounds, SIGABRT);
  tcase_add_test_raise_signal (tc_core, test_list_remove_at_empty, SIGABRT);
  tcase_add_test_raise_signal (tc_core, test_list_remove_at_negative_index, SIGABRT);
  tcase_add_test_raise_signal (tc_core, test_list_remove_first_empty, SIGABRT);
  tcase_add_test_raise_signal (tc_core, test_list_remove_last_empty, SIGABRT);
  tcase_add_test_raise_signal (tc_core, test_list_set_empty, SIGABRT);
  tcase_add_test_raise_signal (tc_core, test_list_set_negative_index, SIGABRT);
  tcase_add_test_raise_signal (tc_core, test_list_out_of_bounds, SIGABRT);
  suite_add_tcase (s, tc_core);

  tc_null_check = tcase_create ("Null");
  tcase_add_test              (tc_null_check, test_list_destroy_null);
  tcase_add_test_raise_signal (tc_null_check, test_list_insert_at_beginning_null, SIGABRT);
  tcase_add_test_raise_signal (tc_null_check, test_list_insert_at_end_null, SIGABRT);
  tcase_add_test_raise_signal (tc_null_check, test_list_insert_at_null, SIGABRT);
  tcase_add_test_raise_signal (tc_null_check, test_list_is_empty_null, SIGABRT);
  tcase_add_test_raise_signal (tc_null_check, test_list_remove_at_null, SIGABRT);
  tcase_add_test_raise_signal (tc_null_check, test_list_remove_first_null, SIGABRT);
  tcase_add_test_raise_signal (tc_null_check, test_list_remove_last_null, SIGABRT);
  tcase_add_test_raise_signal (tc_null_check, test_list_set_null, SIGABRT);
  tcase_add_test_raise_signal (tc_null_check, test_list_size_null, SIGABRT);
  suite_add_tcase (s, tc_null_check);

  return s;
}

int
main (void)
{
  int      number_failed;
  Suite   *s;
  SRunner *sr;

  s = check_list_suite ();
  sr = srunner_create (s);

  srunner_run_all (sr, CK_VERBOSE);
  number_failed = srunner_ntests_failed (sr);
  srunner_free (sr);
  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
