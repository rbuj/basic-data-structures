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

#ifndef STACK_H
#define STACK_H

typedef struct Stack Stack;

Stack * create   (unsigned   capacity);
void    destroy  (Stack    **stack_ptr);
int     is_full  (Stack     *stack);
int     is_empty (Stack     *stack);
void    push     (Stack     *stack,
                  int        value);
int     pop      (Stack     *stack);
int     peek     (Stack     *stack);
void    reverse  (Stack    **stack_ptr);

#endif /* STACK_H */
