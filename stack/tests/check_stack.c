#include <stdlib.h>
#include <check.h>
#include "../src/stack.h"

stack *s = NULL;

void
setup (void)
{
  create (&s, 10);
}

void
teardown (void)
{
  destroy (&s);
}

START_TEST(test_stack_create)
{
  ck_assert (is_empty (s));
  push (s, 10);
  ck_assert (!is_empty (s));
  push (s, 20);
  push (s, 30);
  ck_assert_int_eq (pop (s), 30);
  ck_assert_int_eq (pop (s), 20);
  ck_assert_int_eq (pop (s), 10);
  ck_assert (is_empty (s));
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
