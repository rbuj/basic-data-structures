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
  Node *prev;
  Node *next;
};

struct List
{
  Node *head;
  Node *tail;
  int   size;
};

static Node *
node_create (int   value,
             Node *prev_node,
             Node *next_node)
{
  Node *new_node;

  new_node = (Node *) malloc (sizeof (Node));
  new_node->value = value;
  new_node->prev = prev_node;
  new_node->next = next_node;
  return new_node;
}

static Node *
node_get (Node *it,
          int   i)
{
  for (; i > 0; i--)
    it = it->next;
  return it;
}

static Node *
node_get_tail (Node *it)
{
  while (it->next != NULL)
    it = it->next;
  return it;
}

static void
value_swap (int *a,
            int *b)
{
  int tmp;

  tmp = *a;
  *a  = *b;
  *b  = tmp;
}

List *
list_create (void)
{
  List *list;

  list = (List *) malloc (sizeof (List));
  list->head = NULL;
  list->tail = NULL;
  list->size = 0;
  return list;
}

void
list_destroy (List **list)
{
  Node *it;

  if (*list == NULL)
    return;

  it = (*list)->head;
  while (it != NULL) {
    Node *node = it;
    it = it->next;
    free (node);
  }
  free (*list);
  *list = NULL;
}

int
list_find (List *list,
           int   value)
{
  Node *it;
  int   count = 0;

  if (list == NULL)
    raise (SIGABRT);

  for (it = list->head; it != NULL; it = it->next) {
    if (it->value == value)
      return count;
    count++;
  }
  return INT_MIN;
}

int
list_get (List *list,
          int   index)
{
  if (list_is_empty (list))
    raise (SIGABRT);

  if ((index >= list->size) || (index < 0))
    raise (SIGABRT);

  return node_get (list->head, index)->value;
}

void
list_insert_at (List *list,
                int   index,
                int   value)
{
  if (list == NULL)
    raise (SIGABRT);

  if ((index > list->size) || (index < 0))
    raise (SIGABRT);

  if ((list->head == NULL) && (list->tail == NULL)) {
    list->head = list->tail = node_create (value, NULL, NULL);
  } else {
    Node *ptr;

    if (index == list->size) {
      ptr = list->tail;
      ptr->next = list->tail = node_create (value, ptr, NULL);
    } else {
      Node *new_node;

      ptr = node_get (list->head, index);
      new_node = node_create (value, ptr->prev, ptr);
      if (ptr->prev == NULL) {
        list->head = ptr->prev = new_node;
      } else {
        ptr->prev->next = new_node;
        ptr->prev = new_node;
      }
    }
  }
  list->size++;
}

void
list_insert_at_beginning (List *list,
                          int   value)
{
  Node *old_head;
  Node *new_node;

  if (list == NULL)
    raise (SIGABRT);

  old_head = list->head;
  new_node = list->head = node_create (value, NULL, list->head);
  if (old_head == NULL)
    list->tail = new_node;
  else
    old_head->prev = new_node;
  list->size++;
}

void
list_insert_at_end (List *list,
                    int   value)
{
  Node *old_tail;
  Node *new_node;

  if (list == NULL)
    raise (SIGABRT);

  old_tail = list->tail;
  new_node = list->tail = node_create (value, old_tail, NULL);
  if (old_tail == NULL)
    list->head = new_node;
  else
    old_tail->next = new_node;
  list->size++;
}

int
list_is_empty (List *list)
{
  if (list == NULL)
    raise (SIGABRT);

  return ((list->head == NULL) &&
          (list->tail == NULL) &&
          (list->size == 0));
}

int
list_remove_first (List *list)
{
  int   ret;
  Node *old_head;

  if (list_is_empty (list))
    raise (SIGABRT);

  old_head = list->head;
  ret = old_head->value;
  if ((list->head = old_head->next) == NULL)
    list->tail = NULL;
  else
    list->head->prev = NULL;
  free (old_head);
  list->size--;
  return ret;
}

int
list_remove_last (List *list)
{
  int ret;
  Node *old_tail;

  if (list_is_empty (list))
    raise (SIGABRT);

  old_tail = list->tail;
  ret = old_tail->value;
  if ((list->tail = old_tail->prev) == NULL)
    list->head = NULL;
  else
    list->tail->next = NULL;
  free (old_tail);
  list->size--;
  return ret;
}

void
list_set (List  *list,
          int    index,
          int    value)
{
  if (list_is_empty (list))
    raise (SIGABRT);

  if ((index >= list->size) || (index < 0))
    raise (SIGABRT);

  node_get (list->head, index)->value = value;
}

int
list_size (List *list)
{
  if (list == NULL)
    raise (SIGABRT);

  return list->size;
}

void
list_print (List *list, char *buffer, int len)
{
  Node *it;
  int cx;
  int aux;

  if (list == NULL)
    raise (SIGABRT);

  cx = snprintf (buffer, len, "[");
  if (cx < 0 || cx >= len)
    raise (SIGABRT);

  for (it = list->head; it != NULL; it = it->next) {
    aux = snprintf (buffer + cx, len - cx, " %d", it->value);
    if (aux < 0 || aux + cx >= len)
      raise (SIGABRT);
    cx += aux;

    if (it->next != NULL) {
      aux = snprintf (buffer + cx, len - cx, ",");
      if (aux < 0 || aux + cx >= len)
        raise (SIGABRT);
      cx += aux;
    }
  }
  aux = snprintf (buffer + cx, len - cx, " ]");
  if (aux < 0 || aux + cx >= len)
    raise (SIGABRT);
}
