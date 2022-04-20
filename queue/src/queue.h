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

Queue * create   (unsigned   capacity);
void    destroy  (Queue    **queue_ptr);
void    clean    (Queue     *queue);
int     is_full  (Queue     *queue);
int     is_empty (Queue     *queue);
void    enqueue  (Queue     *queue,
                  int        value);
int     dequeue  (Queue     *queue);
int     front    (Queue     *queue);
int     rear     (Queue     *queue);

#endif /* QUEUE_H */
