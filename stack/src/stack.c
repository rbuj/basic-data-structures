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

#include "stack.h"

struct Stack
{
  int       top;
  unsigned  capacity;
  int      *array;
};

Stack *
create (unsigned capacity)
{
  Stack *stack = (Stack*) malloc (sizeof (Stack));
  stack->capacity = capacity;
  stack->top = -1;
  stack->array = (int*) malloc (capacity * sizeof (int));
  return stack;
}

void
destroy (Stack **stack_ptr)
{
  Stack *stack;

  stack = *stack_ptr;
  if (stack) {
    *stack_ptr = NULL;
    free (stack->array);
    free (stack);
  }
}

int
is_full (Stack *stack)
{
  if (stack == NULL)
    raise (SIGABRT);

  return stack->top == stack->capacity - 1;
}

int
is_empty (Stack *stack)
{
  if (stack == NULL)
    raise (SIGABRT);

  return stack->top == -1;
}

void
push (Stack *stack,
      int    value)
{
  if (is_full (stack))
    return;

  stack->array[++stack->top] = value;
}

int
pop (Stack *stack)
{
  int value = is_empty (stack) ? INT_MIN : stack->array [stack->top--];
  return value;
}

int
peek (Stack *stack)
{
  int value = is_empty (stack) ? INT_MIN : stack->array [stack->top];
  return value;
}

void
reverse (Stack **stack_ptr)
{
  Stack *rev;
  Stack *stack;

  if (*stack_ptr == NULL)
    raise (SIGABRT);

  stack = *stack_ptr;
  rev = create (stack->capacity);
  while (!is_empty (stack))
    push (rev, pop (stack));
  destroy (stack_ptr);
  *stack_ptr = rev;
}
