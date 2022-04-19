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

#ifndef LIST_H
#define LIST_H

typedef struct List List;
typedef struct Node Node;

List * create           (void);
void   destroy          (List **list);
void   add_to_beginning (List  *list, int value);
void   add              (List  *list, int value);
int    remove_first     (List  *list);
int    remove_last      (List  *list);
void   print_list       (List  *list);

#endif /* LIST_H */
