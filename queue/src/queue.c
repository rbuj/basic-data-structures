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
  int       front;
  int       rear;
  int       size;
  unsigned  capacity;
  int      *array;
};

Queue *
create (unsigned capacity)
{
  Queue *queue;

  queue = (Queue*) malloc (sizeof (Queue));
  queue->capacity = capacity;
  queue->rear = capacity - 1;
  queue->size = 0;
  queue->front = 0;
  queue->array = (int*) malloc (capacity * sizeof (int));
  return queue;
}

void
destroy (Queue **queue_ptr)
{
  Queue *queue;

  queue = *queue_ptr;
  if (queue) {
    *queue_ptr = NULL;
    free (queue->array);
    free (queue);
  }
}

int
is_full (Queue *queue)
{
  return queue->size == queue->capacity;
}

int
is_empty (Queue *queue)
{
  return queue->size == 0;
}

void
enqueue (Queue *queue,
         int    value)
{
  if (is_full (queue))
    return;

  queue->rear = (queue->rear + 1) % queue->capacity;
  queue->array [queue->rear] = value;
  queue->size += 1;
}

int
dequeue (Queue *queue)
{
  if (is_empty (queue)) {
    return INT_MIN;
  } else {
    int value;

    value = queue->array [queue->front];
    queue->front = (queue->front + 1) % queue->capacity;
    queue->size -= 1;
    return value;
  }
}

int
front (Queue *queue)
{
  int value = is_empty (queue) ? INT_MIN : queue->array [queue->front];
  return value;
}

int
rear (Queue *queue)
{
  int value = is_empty (queue) ? INT_MIN : queue->array [queue->rear];
  return value;
}
