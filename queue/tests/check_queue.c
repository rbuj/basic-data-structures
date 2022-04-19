#include <stdlib.h>
#include <check.h>
#include "../src/queue.h"

Queue *queue = NULL;

void
setup (void)
{
  create (&queue, 10);
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

Suite *
queue_suite (void)
{
  Suite *s;
  TCase *tc_core;

  s = suite_create ("Queue");
  tc_core = tcase_create ("Core");
  tcase_add_checked_fixture (tc_core, setup, teardown);
  tcase_add_test (tc_core, test_queue_create);
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
