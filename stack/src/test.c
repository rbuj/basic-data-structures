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
#include "stack.h"

int
main (void)
{
  Stack    *stack;
  unsigned  i;
  unsigned  depth = 20;

  stack = create (depth);
  for (i = 0; i < depth; i++)
    push (stack, (int) i);
  for (i = 0; i < depth; i++)
    printf ("%d\n", pop (stack));
  destroy (&stack);

  printf ("\ntest: reverse\n");
  stack = create (depth);
  for (i = 0; i < depth; i++)
    push (stack, (int) i);
  reverse (&stack);
  for (i = 0; i < depth; i++)
    printf ("%d\n", pop (stack));
  destroy (&stack);

  return EXIT_SUCCESS;
}
