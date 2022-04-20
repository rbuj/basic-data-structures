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

Stack * stack_create   (unsigned   capacity);
void    stack_destroy  (Stack    **stack_ptr);

void    stack_clean    (Stack     *stack);
int     stack_is_full  (Stack     *stack);
int     stack_is_empty (Stack     *stack);
void    stack_push     (Stack     *stack,
                        int        value);
int     stack_pop      (Stack     *stack);
int     stack_peek     (Stack     *stack);
void    stack_reverse  (Stack    **stack_ptr);

#endif /* STACK_H */
