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
  Node *tail;
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
node_get (Node *it,
          int   index)
{
  int count = 0;

  while ((index != count) && it) {
    count++;
    it = it->next;
  }
  return it;
}

static Node *
node_get_tail (Node *it)
{
  while (it->next != NULL)
    it = it->next;
  return it;
}

static Node *
node_partition (Node  *head,
                Node  *end,
                Node **new_head,
                Node **new_end)
{
  Node *pivot = end;
  Node *prev = NULL;
  Node *cur = head;
  Node *tail = pivot;

  while (cur != pivot) {
    if (cur->value < pivot->value) {
      if ((*new_head) == NULL)
        (*new_head) = cur;
      prev = cur;
      cur = cur->next;
    } else {
      Node *tmp;

      if (prev)
        prev->next = cur->next;
      tmp = cur->next;
      cur->next = NULL;
      tail->next = cur;
      tail = cur;
      cur = tmp;
    }
  }
  if ((*new_head) == NULL)
    (*new_head) = pivot;
  (*new_end) = tail;
  return pivot;
}

static Node *
node_quick_sort (Node *head,
                 Node *end)
{
  Node *new_head = NULL;
  Node *new_end = NULL;
  Node *pivot;

  if (!head || head == end)
    return head;

  pivot = node_partition (head, end, &new_head, &new_end);
  if (new_head != pivot) {
    Node *tmp;

    tmp = new_head;
    while (tmp->next != pivot)
      tmp = tmp->next;
    tmp->next = NULL;
    new_head = node_quick_sort (new_head, tmp);
    tmp = node_get_tail (new_head);
    tmp->next = pivot;
  }
  pivot->next = node_quick_sort (pivot->next, new_end);

  return new_head;
}

static void
node_swap (Node *a,
           Node *b)
{
  int temp;

  temp = a->value;
  a->value = b->value;
  b->value = temp;
}

List *
list_create (void)
{
  List *list;

  list = (List *) malloc( sizeof (List));
  list->head = NULL;
  list->tail = NULL;
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
list_insert_at (List *list,
                int   index,
                int   value)
{
  if (list == NULL)
    raise (SIGABRT);

  if ((index > list->size) || (index < 0))
    raise (SIGABRT);

  if ((list->head == NULL) || (list->tail == NULL) || (index == 0)) {
    list->head = list->tail = node_create (value, list->head);
  } else {
    if (index == list->size) {
      list->tail->next = node_create (value, NULL);
      list->tail = list->tail->next;
    } else {
      int   i;
      Node *ptr;

      for (i = 0; i < index - 1; i++)
        ptr = ptr->next;
      ptr->next = node_create (value, ptr->next);
    }
  }
  list->size++;
}

void
list_insert_at_beginning (List *list,
                          int   value)
{
  if (list == NULL)
    raise (SIGABRT);

  list->head = node_create (value, list->head);
  if ((list->size == 0) || (list->tail == NULL))
    list->tail = list->head;
  list->size++;
}

void
list_insert_at_end (List *list,
                    int   value)
{
  if (list_is_empty (list)) {
    list->head = list->tail = node_create (value, list->tail);
  } else {
    list->tail->next = node_create (value, NULL);
    list->tail = list->tail->next;
  }
  list->size++;
}

void
list_bubble_sort (List *list)
{
  unsigned swapped;
  int      i;
  struct   Node *it;
  struct   Node *limit = NULL;

  if (list_is_empty (list))
    return;

  do {
    swapped = 0;
    it = list->head;
    while (it->next != limit) {
      if (it->value > it->next->value) {
        node_swap (it, it->next);
        swapped = 1;
      }
      it = it->next;
    }
    limit = it;
  } while (swapped);
}

int
list_find (List *list,
           int   value)
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
list_get (List *list,
          int   index)
{
  int   value;
  Node *it;

  if (list_is_empty (list))
    raise (SIGABRT);

  if ((index >= list->size) || (index < 0))
    raise (SIGABRT);

  if (it = node_get (list->head, index))
    return it->value;

  return INT_MIN;
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

void
list_quick_sort (List *list)
{
  if (list_is_empty (list))
    return;

  list->head = node_quick_sort (list->head, list->tail);
}

int
list_remove_at (List *list,
                int   index)
{
  int   ret;
  Node *ptr;

  if (list_is_empty (list))
    raise (SIGABRT);

  if ((index >= list->size) || (index < 0))
    raise (SIGABRT);

  ptr = list->head;
  if (index == 0) {
    if (list->size == 1)
      list->tail = NULL;
    ret = list->head->value;
    list->head = list->head->next;
    free (ptr);
  } else {
    int   i;
    Node *del;

    for (i = 0; i < index - 1; i++)
      ptr = ptr->next;
    del = ptr->next;
    ret = del->value;
    ptr->next = ptr->next->next;
    if (del->next == NULL)
      list->tail = ptr;
    free (del);
  }
  list->size--;
  return ret;
}

int
list_remove_first (List *list)
{
  int   ret;
  Node *ptr;

  if (list_is_empty (list))
    raise (SIGABRT);

  ptr = list->head;
  ret = list->head->value;
  list->head = list->head->next;
  if (list->head == NULL)
    list->tail = NULL;
  free (ptr);
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
    ret = list->head->value;
    free (list->head);
    list->head = list->tail = NULL;
    list->size = 0;
  } else {
    list->tail = list->head;
    while (list->tail->next->next != NULL)
      list->tail = list->tail->next;
    ret = list->tail->next->value;
    free (list->tail->next);
    list->tail->next = NULL;
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

  if (it = node_get (list->head, index))
    it->value = value;
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

  it = list->head;
  while (it != NULL) {
    aux = snprintf (buffer + cx, len - cx, " %d", it->value);
    if (aux < 0 || aux + cx >= len)
      raise (SIGABRT);
    cx += aux;

    if (it->next) {
      aux = snprintf (buffer + cx, len - cx, ",");
      if (aux < 0 || aux + cx >= len)
        raise (SIGABRT);
      cx += aux;
    }
    it = it->next;
  }
  aux = snprintf (buffer + cx, len - cx, " ]");
  if (aux < 0 || aux + cx >= len)
    raise (SIGABRT);
}
