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

#ifndef LIST_H
#define LIST_H

#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
  int value;
  struct node *next;
} node;

extern void add_to_beginning (node **head, int value);
extern void add              (node **head, int value);
extern int  remove_first     (node **head);
extern int  remove_last      (node **head);
extern void print_list       (node *head);

#endif /* LIST_H */
