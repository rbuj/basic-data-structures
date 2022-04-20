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
stack_create (unsigned capacity)
{
  Stack *stack = (Stack*) malloc (sizeof (Stack));
  stack->capacity = capacity;
  stack->top = -1;
  stack->array = (int*) malloc (capacity * sizeof (int));
  return stack;
}

void
stack_destroy (Stack **stack_ptr)
{
  Stack *stack;

  stack = *stack_ptr;
  if (stack) {
    *stack_ptr = NULL;
    free (stack->array);
    free (stack);
  }
}

void
stack_clean (Stack *stack)
{
  if (stack_is_empty (stack))
    return;

  stack->top = -1;
}


int
stack_is_full (Stack *stack)
{
  if (stack == NULL)
    raise (SIGABRT);

  return stack->top == stack->capacity - 1;
}

int
stack_is_empty (Stack *stack)
{
  if (stack == NULL)
    raise (SIGABRT);

  return stack->top == -1;
}

void
stack_push (Stack *stack,
            int    value)
{
  if (stack_is_full (stack))
    return;

  stack->array[++stack->top] = value;
}

int
stack_pop (Stack *stack)
{
  int value = stack_is_empty (stack) ? INT_MIN : stack->array [stack->top--];
  return value;
}

int
stack_peek (Stack *stack)
{
  int value = stack_is_empty (stack) ? INT_MIN : stack->array [stack->top];
  return value;
}

void
stack_reverse (Stack **stack_ptr)
{
  Stack *rev;
  Stack *stack;

  if (*stack_ptr == NULL)
    raise (SIGABRT);

  stack = *stack_ptr;
  rev = stack_create (stack->capacity);
  while (!stack_is_empty (stack))
    stack_push (rev, stack_pop (stack));
  stack_destroy (stack_ptr);
  *stack_ptr = rev;
}
