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

void
add_to_beginning (node **head,
                  int    value)
{
  node *new_node = (node *) malloc( sizeof (node));
  new_node->value = value;
  new_node->next = *head;
  *head = new_node;
}

void
add (node **head,
     int    value)
{
  if (*head == NULL) {
    add_to_beginning (head, value);
  } else {
    node *ptr = *head;
    while (ptr->next != NULL)
      ptr = ptr->next;
    ptr->next = (node *) malloc (sizeof (node));
    ptr->next->value = value;
    ptr->next->next = NULL;
  }
}

int
remove_first (node **head)
{
  int ret = -1;

  if (*head != NULL) {
    node *ptr = (*head)->next;
    ret = (*head)->value;
    free (*head);
    *head = ptr;
  }

  return ret;
}

int
remove_last (node **head)
{
  int ret = -1;

  if (*head != NULL) {
    if ((*head)->next == NULL) {
      ret = (*head)->value;
      free (*head);
      *head = NULL;
    } else {
      node *ptr = *head;
      while (ptr->next->next != NULL)
        ptr = ptr->next;
      ret = (*head)->next->value;
      free ((*head)->next);
      ptr->next = NULL;
    }
  }

  return ret;
}

void
print_list (node *head)
{
  node *ptr = head;

  printf (" nodes: [");
  while (ptr != NULL) {
    printf (" %d", ptr->value);
    if (ptr->next)
      printf (",");
    ptr = ptr->next;
  }
  printf (" ]\n");
}
