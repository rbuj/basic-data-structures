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

START_TEST (test_list_bubble_sort)
{
  char buffer [100];
  int i;

  for (i = 1; i <= 10; i++)
    list_insert_at_beginning (list, i);

  list_print (list, buffer, 100);
  ck_assert_str_eq (buffer, "[ 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 ]");

  list_bubble_sort (list);
  list_print (list, buffer, 100);
  ck_assert_str_eq (buffer, "[ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 ]");
}

START_TEST (test_list_bubble_sort_empty)
{
  char buffer [100];

  list_bubble_sort (list);
  list_print (list, buffer, 100);
  ck_assert_str_eq (buffer, "[ ]");
}

START_TEST (test_list_quick_sort)
{
  char buffer [100];
  int i;

  for (i = 1; i <= 10; i++)
    list_insert_at_beginning (list, i);

  list_print (list, buffer, 100);
  ck_assert_str_eq (buffer, "[ 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 ]");

  list_quick_sort (list);
  list_print (list, buffer, 100);
  ck_assert_str_eq (buffer, "[ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 ]");
}

START_TEST (test_list_quick_sort_empty)
{
  char buffer [100];

  list_quick_sort (list);
  list_print (list, buffer, 100);
  ck_assert_str_eq (buffer, "[ ]");
}

START_TEST (test_list_find)
{
  int i;

  for (i = 10; i > 0; i--)
    list_insert_at_beginning (list, i);

  for (i = 1; i <= 10; i++)
    ck_assert_int_eq (list_find (list, i), i - 1);
}

START_TEST (test_list_find_empty)
{
  ck_assert (list_is_empty (list));
  ck_assert_int_eq (list_find (list, 0), INT_MIN);
}

START_TEST (test_list_get)
{
  int i;

  for (i = 10; i > 0; i--)
    list_insert_at_beginning (list, i);

  for (i = 1; i <= 10; i++)
    ck_assert_int_eq (list_get (list, i - 1),  i);
}

START_TEST (test_list_get_empty)
{
  ck_assert (list_is_empty (list));
  (void) list_get (list, 0);
}

START_TEST (test_list_get_negative_index)
{
  ck_assert (list_is_empty (list));
  list_insert_at_beginning (list, 3);
  list_insert_at_beginning (list, 2);
  list_insert_at_beginning (list, 1);
  ck_assert_int_eq (list_size (list), 3);
  (void) list_get (list, -1);
}

START_TEST (test_list_get_out_of_bounds)
{
  ck_assert (list_is_empty (list));
  list_insert_at_beginning (list, 3);
  list_insert_at_beginning (list, 2);
  list_insert_at_beginning (list, 1);
  ck_assert_int_eq (list_size (list), 3);
  (void) list_get (list, 3);
}

START_TEST (test_list_insert_at_beginning)
{
  char buffer [100];
  int i;

  for (i = 10; i > 0; i--)
    list_insert_at_beginning (list, i);

  list_print (list, buffer, 100);
  ck_assert_str_eq (buffer, "[ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 ]");
}

START_TEST (test_list_insert_at_beginning_empty)
{
  ck_assert (list_is_empty (list));
  list_insert_at_beginning (list, 10);
  ck_assert_int_eq (list_get (list, 0), 10);
  ck_assert_int_eq (list_size (list), 1);
}

START_TEST (test_list_insert_at_end)
{
  char buffer [100];
  int i;

  for (i = 1; i <= 10; i++)
    list_insert_at_end (list, i);

  list_print (list, buffer, 100);
  ck_assert_str_eq (buffer, "[ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 ]");
}

START_TEST (test_list_insert_at_end_empty)
{
  ck_assert (list_is_empty (list));
  list_insert_at_end (list, 10);
  ck_assert_int_eq (list_get (list, 0), 10);
  ck_assert_int_eq (list_size (list), 1);
}

START_TEST (test_list_insert_at)
{
  char buffer [100];

  list_insert_at_beginning (list, 4);
  list_insert_at_beginning (list, 2);

  list_insert_at (list, 2, 5);
  list_insert_at (list, 0, 1);
  list_insert_at (list, 2, 3);

  list_print (list, buffer, 100);
  ck_assert_str_eq (buffer, "[ 1, 2, 3, 4, 5 ]");
}

START_TEST (test_list_insert_at_empty)
{
  ck_assert (list_is_empty (list));
  list_insert_at (list, 0, 10);
  ck_assert_int_eq (list_get (list, 0), 10);
  ck_assert_int_eq (list_size (list), 1);
}

START_TEST (test_list_insert_at_negative_index)
{
  ck_assert (list_is_empty (list));
  list_insert_at_beginning (list, 3);
  list_insert_at_beginning (list, 2);
  list_insert_at_beginning (list, 1);
  ck_assert (!list_is_empty (list));
  list_insert_at (list, -1, 1);
}

START_TEST (test_list_insert_at_out_of_bounds)
{
  ck_assert (list_is_empty (list));
  list_insert_at_beginning (list, 3);
  list_insert_at_beginning (list, 2);
  list_insert_at_beginning (list, 1);
  ck_assert_int_eq (list_size (list), 3);
  list_insert_at (list, 3, 4);
  ck_assert_int_eq (list_get (list, 3), 4);
  ck_assert_int_eq (list_size (list), 4);
  list_insert_at (list, 5, 6);
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
  list_insert_at (list, 0, 1);
  ck_assert_int_eq (list_get (list, 0), 1);
}

START_TEST (test_list_is_empty)
{
  ck_assert (list_is_empty (list));
  list_insert_at_end (list, 20);
  ck_assert (!list_is_empty (list));
}

START_TEST (test_list_remove_at)
{
  char buffer [100];
  int i;

  for (i = 10; i > 0; i--)
    list_insert_at_beginning (list, i);

  list_print (list, buffer, 100);
  ck_assert_str_eq (buffer, "[ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 ]");

  ck_assert_int_eq (list_remove_at (list, 9), 10);
  ck_assert_int_eq (list_remove_at (list, 0), 1);
  ck_assert_int_eq (list_remove_at (list, 3), 5);

  list_print (list, buffer, 100);
  ck_assert_str_eq (buffer, "[ 2, 3, 4, 6, 7, 8, 9 ]");
}

START_TEST (test_list_remove_at_empty)
{
  ck_assert (list_is_empty (list));
  (void) list_remove_at (list, 0);
}

START_TEST (test_list_remove_at_negative_index)
{
  list_insert_at_beginning (list, 3);
  list_insert_at_beginning (list, 2);
  list_insert_at_beginning (list, 1);
  ck_assert_int_eq (list_size (list), 3);
  (void) list_remove_at (list, -1);
}

START_TEST (test_list_remove_at_out_of_bounds)
{
  list_insert_at_beginning (list, 3);
  list_insert_at_beginning (list, 2);
  list_insert_at_beginning (list, 1);
  ck_assert_int_eq (list_size (list), 3);
  (void) list_remove_at (list, 3);
}

START_TEST (test_list_remove_first)
{
  char buffer [100];
  int i;

  for (i = 10; i > 0; i--)
    list_insert_at_beginning (list, i);

  list_print (list, buffer, 100);
  ck_assert_str_eq (buffer, "[ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 ]");

  ck_assert_int_eq (list_remove_first (list), 1);

  list_print (list, buffer, 100);
  ck_assert_str_eq (buffer, "[ 2, 3, 4, 5, 6, 7, 8, 9, 10 ]");
}

START_TEST (test_list_remove_first_empty)
{
  ck_assert (list_is_empty (list));
  (void) list_remove_first (list);
}

START_TEST (test_list_remove_last)
{
  char buffer [100];
  int i;

  for (i = 1; i <= 10; i++)
    list_insert_at_end (list, i);

  list_print (list, buffer, 100);
  ck_assert_str_eq (buffer, "[ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 ]");

  ck_assert_int_eq (list_remove_last (list), 10);

  list_print (list, buffer, 100);
  ck_assert_str_eq (buffer, "[ 1, 2, 3, 4, 5, 6, 7, 8, 9 ]");
}

START_TEST (test_list_remove_last_empty)
{
  ck_assert (list_is_empty (list));
  (void) list_remove_last (list);
}

START_TEST (test_list_set)
{
  list_insert_at_beginning (list, 3);
  list_insert_at_beginning (list, 2);
  list_insert_at_beginning (list, 1);
  ck_assert_int_eq (list_size (list), 3);
  list_set (list, 0, 10);
  ck_assert_int_eq (list_get (list, 0), 10);
  list_set (list, 1, 7);
  ck_assert_int_eq (list_get (list, 1), 7);
  list_set (list, 2, 20);
  ck_assert_int_eq (list_get (list, 2), 20);
}

START_TEST (test_list_set_empty)
{
  ck_assert (list_is_empty (list));
  list_set (list, 0, 1);
}

START_TEST (test_list_set_negative_index)
{
  list_insert_at_beginning (list, 3);
  list_insert_at_beginning (list, 2);
  list_insert_at_beginning (list, 1);
  ck_assert_int_eq (list_size (list), 3);
  list_set (list, -1, 1);
}

START_TEST (test_list_set_out_of_bounds)
{
  list_insert_at_beginning (list, 10);
  ck_assert (!list_is_empty (list));
  ck_assert_int_eq (list_size (list), 1);
  list_set (list, 1, 1);
}

/* tc_null_check */

START_TEST (test_list_bubble_sort_null)
{
  ck_assert (list == NULL);
  list_bubble_sort (list);
}

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

START_TEST (test_list_quick_sort_null)
{
  ck_assert (list == NULL);
  list_quick_sort (list);
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
  /* test_list_find */
  tcase_add_test              (tc_core, test_list_find);
  tcase_add_test              (tc_core, test_list_find_empty);
  /* list_get */
  tcase_add_test              (tc_core, test_list_get);
  tcase_add_test_raise_signal (tc_core, test_list_get_empty, SIGABRT);
  tcase_add_test_raise_signal (tc_core, test_list_get_negative_index, SIGABRT);
  tcase_add_test_raise_signal (tc_core, test_list_get_out_of_bounds, SIGABRT);
  /* list_insert_at_beginning */
  tcase_add_test              (tc_core, test_list_insert_at_beginning);
  tcase_add_test              (tc_core, test_list_insert_at_beginning_empty);
  /* list_insert_at_end */
  tcase_add_test              (tc_core, test_list_insert_at_end);
  tcase_add_test              (tc_core, test_list_insert_at_end_empty);
  /* list_insert_at */
  tcase_add_test              (tc_core, test_list_insert_at);
  tcase_add_test              (tc_core, test_list_insert_at_empty);
  tcase_add_test_raise_signal (tc_core, test_list_insert_at_negative_index, SIGABRT);
  tcase_add_test_raise_signal (tc_core, test_list_insert_at_out_of_bounds, SIGABRT);
  tcase_add_test              (tc_core, test_list_insert_at_zero_index);
  tcase_add_test              (tc_core, test_list_insert_at_zero_index_empty);
  /* list_remove_at */
  tcase_add_test              (tc_core, test_list_remove_at);
  tcase_add_test_raise_signal (tc_core, test_list_remove_at_empty, SIGABRT);
  tcase_add_test_raise_signal (tc_core, test_list_remove_at_negative_index, SIGABRT);
  tcase_add_test_raise_signal (tc_core, test_list_remove_at_out_of_bounds, SIGABRT);
  /* remove_first */
  tcase_add_test              (tc_core, test_list_remove_first);
  tcase_add_test_raise_signal (tc_core, test_list_remove_first_empty, SIGABRT);
  /* list_remove_last */
  tcase_add_test              (tc_core, test_list_remove_last);
  tcase_add_test_raise_signal (tc_core, test_list_remove_last_empty, SIGABRT);
  /* test_list_set */
  tcase_add_test              (tc_core, test_list_set);
  tcase_add_test_raise_signal (tc_core, test_list_set_empty, SIGABRT);
  tcase_add_test_raise_signal (tc_core, test_list_set_negative_index, SIGABRT);
  tcase_add_test_raise_signal (tc_core, test_list_set_out_of_bounds, SIGABRT);
  /* sort */
  tcase_add_test              (tc_core, test_list_bubble_sort);
  tcase_add_test              (tc_core, test_list_bubble_sort_empty);
  tcase_add_test              (tc_core, test_list_quick_sort);
  tcase_add_test              (tc_core, test_list_quick_sort_empty);
  /* add tc_core */
  suite_add_tcase (s, tc_core);

  tc_null_check = tcase_create ("Null");
  tcase_add_test_raise_signal (tc_null_check, test_list_bubble_sort_null, SIGABRT);
  tcase_add_test              (tc_null_check, test_list_destroy_null);
  tcase_add_test_raise_signal (tc_null_check, test_list_insert_at_null, SIGABRT);
  tcase_add_test_raise_signal (tc_null_check, test_list_insert_at_beginning_null, SIGABRT);
  tcase_add_test_raise_signal (tc_null_check, test_list_insert_at_end_null, SIGABRT);
  tcase_add_test_raise_signal (tc_null_check, test_list_is_empty_null, SIGABRT);
  tcase_add_test_raise_signal (tc_null_check, test_list_quick_sort_null, SIGABRT);
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
