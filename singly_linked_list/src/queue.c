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

#include "queue.h"
#include "list.h"

struct Queue
{
  List *list;
};

Queue *
queue_create (unsigned)
{
  Queue *queue;

  queue = (Queue*) malloc (sizeof (Queue));
  queue->list = list_create ();
  return queue;
}

void
queue_destroy (Queue **queue_ptr)
{
  Queue *queue;

  queue = *queue_ptr;
  if (queue) {
    list_destroy (&queue->list);
    free (queue);
  }
}

int
queue_is_empty (Queue *queue)
{
  if (queue == NULL) {
    fprintf (stderr, "The queue is NULL.\n");
    raise (SIGABRT);
  }

  return list_is_empty (queue->list);
}

void
queue_enqueue (Queue *queue,
               int    value)
{
  if (queue == NULL) {
    fprintf (stderr, "The queue is NULL.\n");
    raise (SIGABRT);
  }

  list_insert_at_end (queue->list, value);
}

int
queue_dequeue (Queue *queue)
{
  if (queue_is_empty (queue)) {
    return INT_MIN;
  } else {
    return list_remove_first (queue->list);
  }
}
