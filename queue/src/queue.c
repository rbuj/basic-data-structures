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
#include "queue.h"

struct Queue
{
  int front, rear, size;
  unsigned capacity;
  int *array;
};

void
create (Queue    **q,
        unsigned   capacity)
{
  *q = (Queue*) malloc (sizeof (Queue));
  (*q)->capacity = capacity;
  (*q)->rear = capacity - 1;
  (*q)->size = 0;
  (*q)->front = 0;
  (*q)->array = (int*) malloc (capacity * sizeof (int));
}

void
destroy (Queue **q)
{
  free ((*q)->array);
  free (*q);
  *q = NULL;
}

int
is_full (Queue *q)
{
  return q->size == q->capacity;
}

int
is_empty (Queue *q)
{
  return q->size == 0;
}

void
enqueue (Queue *q,
         int    value)
{
  if (is_full (q))
    return;

  q->rear = (q->rear + 1) % q->capacity;
  q->array [q->rear] = value;
  q->size += 1;
}

int
dequeue (Queue *q)
{
  int value = q->array [q->front];
  q->front = (q->front + 1) % q->capacity;
  q->size -= 1;
  return value;
}

int
front (Queue *q)
{
  int value = is_empty (q) ? INT_MIN : q->array [q->front];
  return value;
}

int
rear (Queue *q)
{
  int value = is_empty (q) ? INT_MIN : q->array [q->rear];
  return value;
}
