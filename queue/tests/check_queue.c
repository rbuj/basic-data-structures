#include <stdlib.h>
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

START_TEST(test_queue_create)
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

START_TEST(test_destroy_null_collection)
{
  Queue *q = NULL;
  destroy (&q);
}

START_TEST(test_queue_full)
{
  int i;

  ck_assert (!is_full (queue));
  for (i = 0; i < QUEUE_CAPACITY; i++)
    enqueue (queue, i);
  ck_assert (is_full (queue));
}

START_TEST(test_queue_clean)
{
  int i;

  ck_assert (!is_full (queue));
  for (i = 0; i < QUEUE_CAPACITY - 1; i++)
    enqueue (queue, i);
  clean (queue);
  enqueue (queue, i + 1);
  ck_assert (!is_full (queue));
}


Suite *
queue_suite (void)
{
  Suite *s;
  TCase *tc_core;

  s = suite_create ("Queue");

  tc_core = tcase_create ("Core");
  tcase_add_checked_fixture (tc_core, setup, teardown);
  tcase_add_test (tc_core, test_queue_create);
  tcase_add_test (tc_core, test_destroy_null_collection);
  tcase_add_test (tc_core, test_queue_full);
  tcase_add_test (tc_core, test_queue_clean);
  suite_add_tcase (s, tc_core);

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

  srunner_run_all (sr, CK_NORMAL);
  number_failed = srunner_ntests_failed (sr);
  srunner_free (sr);
  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
