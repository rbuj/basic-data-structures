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

#include <stdio.h>
#include <stdlib.h>
#include "list.h"

struct Node
{
  int value;
  Node *next;
};

struct List
{
  Node *head;
};

static Node *
create_node (int   value,
             Node *next_node)
{
  Node *new_node = (Node *) malloc (sizeof (Node));
  new_node->value = value;
  new_node->next = next_node;
  return new_node;
}

List *
list_create (void)
{
  List *list = (List *) malloc( sizeof (List));
  list->head = NULL;
  return list;
}

void
list_destroy (List **list)
{
  Node *ptr;

  if (list == NULL)
    return;

  ptr = (*list)->head;
  while (ptr != NULL) {
    (void) list_remove_first (*list);
    ptr = (*list)->head;
  }
  free (*list);
  *list = NULL;
}

void
list_add_to_beginning (List *list,
                  int   value)
{
  list->head = create_node (value, list->head);
}

void
list_add (List *list,
          int   value)
{
  if (list->head == NULL) {
    list_add_to_beginning (list, value);
  } else {
    Node *ptr = list->head;
    while (ptr->next != NULL)
      ptr = ptr->next;
    ptr->next = create_node (value, NULL);
  }
}

int
list_remove_first (List *list)
{
  int ret = -1;

  if (list != NULL && list->head != NULL) {
    Node *ptr = list->head->next;
    ret = list->head->value;
    free (list->head);
    list->head = ptr;
  }

  return ret;
}

int
list_remove_last (List *list)
{
  int ret = -1;

  if (list != NULL && list->head != NULL) {
    if (list->head->next == NULL) {
      ret = list->head->value;
      free (list->head);
      list->head = NULL;
    } else {
      Node *ptr = list->head;
      while (ptr->next->next != NULL)
        ptr = ptr->next;
      ret = ptr->next->value;
      free (ptr->next);
      ptr->next = NULL;
    }
  }

  return ret;
}

void
list_print (List *list)
{
  Node *ptr;

  if (list == NULL)
    return;

  printf (" nodes: [");
  ptr = list->head;
  while (ptr != NULL) {
    printf (" %d", ptr->value);
    if (ptr->next)
      printf (",");
    ptr = ptr->next;
  }
  printf (" ]\n");
}
