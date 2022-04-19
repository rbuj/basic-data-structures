#include <stdlib.h>
#include <check.h>
#include "../src/stack.h"

START_TEST(test_money_pop)
{
  stack *s = NULL;

  create (&s, 10);
  ck_assert (is_empty (s));
  push (s, 10);
  ck_assert (!is_empty (s));
  push (s, 20);
  push (s, 30);
  ck_assert_int_eq (pop (s), 30);
  ck_assert_int_eq (pop (s), 20);
  ck_assert_int_eq (pop (s), 10);
  ck_assert (is_empty (s));
  destroy (&s);
}

int
main (void)
{
  return EXIT_SUCCESS;
}
