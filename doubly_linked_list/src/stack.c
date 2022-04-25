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

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

#include "list.h"
#include "stack.h"

struct Stack
{
  List *list;
};

Stack *
stack_create (void)
{
  Stack *stack;

  stack = (Stack*) malloc (sizeof (Stack));
  stack->list = list_create ();
  return stack;
}

void
stack_destroy (Stack **stack_ptr)
{
  Stack *stack;

  stack = *stack_ptr;
  if (stack) {
    *stack_ptr = NULL;
    list_destroy (&stack->list);
    free (stack);
  }
}

int
stack_is_empty (Stack *stack)
{
  if (stack == NULL) {
    fprintf (stderr, "The stack is NULL.\n");
    raise (SIGABRT);
  }

  return list_is_empty (stack->list);
}

int
stack_peek (Stack *stack)
{
  if (stack == NULL) {
    fprintf (stderr, "The stack is NULL.\n");
    raise (SIGABRT);
  }
  return list_get_tail (stack->list);
}

int
stack_pop (Stack *stack)
{
  return stack_is_empty (stack) ? INT_MIN : list_remove_last (stack->list);
}

void
stack_push (Stack *stack,
            int    value)
{
  if (stack == NULL) {
    fprintf (stderr, "The stack is NULL.\n");
    raise (SIGABRT);
  }

  list_insert_at_end (stack->list, value);
}
