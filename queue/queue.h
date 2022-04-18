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

#ifndef QUEUE_H
#define QUEUE_H

#include <stdio.h>
#include <stdlib.h>

typedef struct queue
{
  int front, rear, size;
  unsigned capacity;
  int *array;
} queue;

extern void  create   (queue **q, unsigned capacity);
extern void  destroy  (queue **q);
extern int   is_full  (queue  *q);
extern int   is_empty (queue  *q);
extern void  enqueue  (queue  *q, int      value);
extern int   dequeue  (queue  *q);
extern int   front    (queue  *q);
extern int   rear     (queue  *q);

#endif /* QUEUE_H */
