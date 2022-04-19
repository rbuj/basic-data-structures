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
#include "stack.h"

struct Stack
{
  int top;
  unsigned capacity;
  int *array;
};

void
create (Stack    **s,
        unsigned   capacity)
{
  *s = (Stack*) malloc (sizeof (Stack));
  (*s)->capacity = capacity;
  (*s)->top = -1;
  (*s)->array = (int*) malloc (capacity * sizeof (int));
}

void
destroy (Stack **s)
{
  free ((*s)->array);
  free (*s);
  *s = NULL;
}

int
is_full (Stack *s)
{
  return s->top == s->capacity - 1;
}

int
is_empty (Stack *s)
{
  return s->top == -1;
}

void
push (Stack *s,
      int    value)
{
  if (is_full (s))
    return;
  s->array[++s->top] = value;
}

int
pop (Stack *s)
{
  int value = is_empty (s) ? INT_MIN : s->array [s->top--];
  return value;
}

int
peek (Stack *s)
{
  int value = is_empty (s) ? INT_MIN : s->array [s->top];
  return value;
}

void
reverse (Stack **s)
{
  Stack *rev = NULL;

  create (&rev, (*s)->capacity);
  while (!is_empty (*s))
    push (rev, pop (*s));
  destroy (s);
  *s = rev;
}
