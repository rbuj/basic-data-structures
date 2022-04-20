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

  list = list_create ();
  list_add (list, 2);
  list_add (list, 3);
  list_add (list, 4);
  list_add (list, 5);
  list_add (list, 6);
  list_add_to_beginning (list, 1);
  list_remove_last (list);

  list_print (list);

  list_destroy (&list);

  return EXIT_SUCCESS;
}
