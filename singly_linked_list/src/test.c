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

int
main (void)
{
  List *list;
  char buffer [100];

  list = list_create ();
  list_insert_at_end (list, 2);
  printf ("Index (2) : %d\n", list_find (list, 2));
  list_insert_at_end (list, 6);
  list_insert_at_end (list, 4);
  list_insert_at_end (list, 5);
  list_insert_at_end (list, 3);
  list_insert_at_beginning (list, 1);
  printf ("Index (6) : %d\n", list_find (list, 6));
  printf ("Index (2) : %d\n", list_find (list, 2));
  printf ("Value (4) : %d\n", list_get (list, 4));
  printf ("Size : %d\n", list_size (list));
  list_remove_last (list);
  printf ("Size : %d\n", list_size (list));

  list_print (list, buffer, 100);
  printf ("%s\n", buffer);
/*  list_bubble_sort (list); */
  list_quick_sort (list);
  list_print (list, buffer, 100);
  printf ("%s\n", buffer);
  list_destroy (&list);

  return EXIT_SUCCESS;
}
