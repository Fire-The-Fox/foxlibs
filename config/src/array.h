/*This file is part of foxlibs
Copyright (C) 2022 Ján Gajdoš

This library is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this library.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef ARRAY_H
#define ARRAY_H

#include "types.h"

typedef struct {
    String *data;
    unsigned int length;
} StringArray;

typedef struct {
    Number *data;
    unsigned int length;
} NumberArray;

typedef struct {
    Bool *data;
    unsigned int length;
} BoolArray;

StringArray newStringArray();
NumberArray newNumberArray();
BoolArray newBoolArray();

void pushStringArray(StringArray *array, String value);
void pushNumberArray(NumberArray *array, Number value);
void pushBoolArray(BoolArray *array, Bool value);

void freeStringArray(StringArray *array);
void freeNumberArray(NumberArray *array);
void freeBoolArray(BoolArray *array);

#endif