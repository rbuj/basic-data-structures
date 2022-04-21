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
#include <limits.h>
#include <signal.h>

#include "list.h"

struct Node
{
  int   value;
  Node *next;
};

struct List
{
  Node *head;
  int   size;
};

static Node *
node_create (int   value,
             Node *next_node)
{
  Node *new_node;

  new_node = (Node *) malloc (sizeof (Node));
  new_node->value = value;
  new_node->next = next_node;
  return new_node;
}

static Node *
node_last (List *list)
{
    Node *it;

    it = list->head;
    while (it->next != NULL)
      it = it->next;
    return it;
}

static Node *
node_get (List *list,
          int   index)
{
  Node *it;
  int   count = 0;

  it = list->head;
  while ((index != count) && it) {
    count++;
    it = it->next;
  }
  return it;
}

List *
list_create (void)
{
  List *list;

  list = (List *) malloc( sizeof (List));
  list->head = NULL;
  list->size = 0;
  return list;
}

void
list_destroy (List **list)
{
  Node *ptr;

  if (*list == NULL)
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
  if (list == NULL)
    raise (SIGABRT);

  list->head = node_create (value, list->head);
  list->size++;
}

void
list_add (List *list,
          int   value)
{
  if (list == NULL)
    raise (SIGABRT);

  if (list->head == NULL) {
    list_add_to_beginning (list, value);
  } else {
    (node_last (list))->next = node_create (value, NULL);
    list->size++;
  }
}

int
list_find (List  *list,
           int    value)
{
  Node *it;
  int   count = 0;

  if (list == NULL)
    raise (SIGABRT);

  it = list->head;
  while (it && (it->value != value)) {
    count++;
    it = it->next;
  }
  if (it)
    return count;
  return INT_MIN;
}

int
list_get (List  *list,
          int    index)
{
  int   value;
  Node *it;

  if (list_is_empty (list))
    raise (SIGABRT);

  if ((index >= list->size) || (index < 0))
    raise (SIGABRT);

  if (it = node_get (list, index))
    return it->value;

  return INT_MIN;
}

int
list_is_empty (List  *list)
{
  if (list == NULL)
    raise (SIGABRT);

  return list->head == NULL;
}

int
list_remove_first (List *list)
{
  int   ret;
  Node *ptr;

  if (list_is_empty (list))
    raise (SIGABRT);

  ptr = list->head->next;
  ret = list->head->value;
  free (list->head);
  list->head = ptr;
  list->size--;

  return ret;
}

int
list_remove_last (List *list)
{
  int ret;

  if (list_is_empty (list))
    raise (SIGABRT);

  if (list->head->next == NULL) {
    ret = list_remove_first (list);
  } else {
    Node *ptr = list->head;
    while (ptr->next->next != NULL)
      ptr = ptr->next;
    ret = ptr->next->value;
    free (ptr->next);
    ptr->next = NULL;
    list->size--;
  }
  return ret;
}

void
list_set (List  *list,
          int    index,
          int    value)
{
  Node *it;

  if (list_is_empty (list))
    raise (SIGABRT);

  if ((index >= list->size) || (index < 0))
    raise (SIGABRT);

  if (it = node_get (list, index))
    it->value = value;
}

int
list_size (List  *list)
{
  if (list == NULL)
    raise (SIGABRT);

  return list->size;
}

void
list_print (List *list)
{
  Node *it;

  if (list == NULL)
    raise (SIGABRT);

  printf (" nodes: [");
  it = list->head;
  while (it != NULL) {
    printf (" %d", it->value);
    if (it->next)
      printf (",");
    it = it->next;
  }
  printf (" ]\n");
}
