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

typedef struct Queue Queue;

Queue * queue_create   (unsigned   capacity);
void    queue_destroy  (Queue    **queue_ptr);
void    queue_clean    (Queue     *queue);
int     queue_is_full  (Queue     *queue);
int     queue_is_empty (Queue     *queue);
void    queue_enqueue  (Queue     *queue,
                        int        value);
int     queue_dequeue  (Queue     *queue);
int     queue_front    (Queue     *queue);
int     queue_rear     (Queue     *queue);

#endif /* QUEUE_H */
