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

#include "../src/queue.h"

Queue *queue = NULL;

Suite * check_queue_suite (void);
void setup (void);
void teardown (void);

void
setup (void)
{
  queue = queue_create ();
}

void
teardown (void)
{
  queue_destroy (&queue);
}

START_TEST (test_queue)
{
  ck_assert (queue_is_empty (queue));

  queue_enqueue (queue, 10);
  ck_assert (!queue_is_empty (queue));

  queue_enqueue (queue, 20);

  ck_assert_int_eq (queue_dequeue (queue), 10);
  ck_assert_int_eq (queue_dequeue (queue), 20);
  ck_assert (queue_is_empty (queue));
}

START_TEST (test_queue_dequeue_empty)
{
  ck_assert (queue_is_empty (queue));
  ck_assert (queue_dequeue (queue) == INT_MIN);
}

/* tc_null_check */

START_TEST (test_queue_dequeue_null)
{
  ck_assert (queue == NULL);
  (void) queue_dequeue (queue);
}

START_TEST (test_queue_destroy_null)
{
  ck_assert (queue == NULL);
  queue_destroy (&queue);
}

START_TEST (test_queue_enqueue_null)
{
  ck_assert (queue == NULL);
  queue_enqueue (queue, 1);
}

START_TEST (test_queue_is_empty_null)
{
  ck_assert (queue == NULL);
  queue_is_empty (queue);
}

Suite *
check_queue_suite (void)
{
  Suite *s;
  TCase *tc_core;
  TCase *tc_null_check;

  s = suite_create ("Queue");

  tc_core = tcase_create ("Core");
  tcase_add_checked_fixture   (tc_core, setup, teardown);
  tcase_add_test              (tc_core, test_queue);
  tcase_add_test              (tc_core, test_queue_dequeue_empty);
  suite_add_tcase (s, tc_core);

  tc_null_check = tcase_create("Null");
  tcase_add_test              (tc_null_check, test_queue_destroy_null);
  tcase_add_test_raise_signal (tc_null_check, test_queue_dequeue_null, SIGABRT);
  tcase_add_test_raise_signal (tc_null_check, test_queue_enqueue_null, SIGABRT);
  tcase_add_test_raise_signal (tc_null_check, test_queue_is_empty_null, SIGABRT);
  suite_add_tcase (s, tc_null_check);

  return s;
}

int
main (void)
{
  int      number_failed;
  Suite   *s;
  SRunner *sr;

  s = check_queue_suite ();
  sr = srunner_create (s);

  srunner_run_all (sr, CK_VERBOSE);
  number_failed = srunner_ntests_failed (sr);
  srunner_free (sr);
  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
