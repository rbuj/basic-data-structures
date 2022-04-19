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

typedef struct stack stack;

void  create   (stack **s, unsigned capacity);
void  destroy  (stack **s);
int   is_full  (stack  *s);
int   is_empty (stack  *s);
void  push     (stack  *s, int      value);
int   pop      (stack  *s);
int   peek     (stack  *s);
void  reverse  (stack **s);

#endif /* STACK_H */
