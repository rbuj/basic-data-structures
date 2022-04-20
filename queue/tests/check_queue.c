#include <stdlib.h>
#include <limits.h>
#include <signal.h>
#include <check.h>
#include "../src/queue.h"

#define QUEUE_CAPACITY 10

Queue *queue = NULL;

void
setup (void)
{
  queue = create (QUEUE_CAPACITY);
}

void
teardown (void)
{
  destroy (&queue);
}

START_TEST (test_queue_clean)
{
  int i;

  ck_assert (!is_full (queue));
  for (i = 0; i < QUEUE_CAPACITY - 1; i++)
    enqueue (queue, i);
  clean (queue);
  enqueue (queue, i + 1);
  ck_assert (!is_full (queue));
}

START_TEST (test_queue_create)
{
  ck_assert (is_empty (queue));
  ck_assert (!is_full (queue));

  enqueue (queue, 10);
  ck_assert (!is_empty (queue));

  enqueue (queue, 20);

  ck_assert_int_eq (dequeue (queue), 10);
  ck_assert_int_eq (dequeue (queue), 20);
  ck_assert (is_empty (queue));
}

START_TEST (test_queue_is_full)
{
  int i;

  ck_assert (!is_full (queue));
  for (i = 0; i < QUEUE_CAPACITY; i++)
    enqueue (queue, i);
  ck_assert (is_full (queue));
}

/* tc_null_check */

START_TEST (test_queue_clean_null)
{
  ck_assert (queue == NULL);
  clean (queue);
}

START_TEST (test_queue_destroy_null)
{
  ck_assert (queue == NULL);
  destroy (&queue);
}

START_TEST (test_queue_is_full_null)
{
  ck_assert (queue == NULL);
  is_full (queue);
}

START_TEST (test_queue_is_empty_null)
{
  ck_assert (queue == NULL);
  is_empty (queue);
}

Suite *
queue_suite (void)
{
  Suite *s;
  TCase *tc_core;
  TCase *tc_null_check;

  s = suite_create ("Queue");

  tc_core = tcase_create ("Core");
  tcase_add_checked_fixture (tc_core, setup, teardown);
  tcase_add_test (tc_core, test_queue_clean);
  tcase_add_test (tc_core, test_queue_create);
  tcase_add_test (tc_core, test_queue_is_full);
  suite_add_tcase (s, tc_core);

  tc_null_check = tcase_create("Null");
  tcase_add_test_raise_signal (tc_null_check, test_queue_clean_null, SIGABRT);
  tcase_add_test (tc_null_check, test_queue_destroy_null);
  tcase_add_test_raise_signal (tc_null_check, test_queue_is_full_null, SIGABRT);
  tcase_add_test_raise_signal (tc_null_check, test_queue_is_empty_null, SIGABRT);
  suite_add_tcase(s, tc_null_check);

  return s;
}

int
main (void)
{
  int number_failed;
  Suite *s;
  SRunner *sr;

  s = queue_suite ();
  sr = srunner_create (s);

  srunner_run_all (sr, CK_VERBOSE);
  number_failed = srunner_ntests_failed (sr);
  srunner_free (sr);
  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
