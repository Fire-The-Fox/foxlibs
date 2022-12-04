/*
This file is part of foxlibs
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

#include <stdlib.h>

#include "array.h"

StringArray newStringArray() {
    StringArray array;
    array.data = NULL;
    array.length = 0;
    return array;
}

NumberArray newNumberArray() {
    NumberArray array;
    array.data = NULL;
    array.length = 0;
    return array;
}

BoolArray newBoolArray() {
    BoolArray array;
    array.data = NULL;
    array.length = 0;
    return array;
}

void pushStringArray(StringArray *array, String value) {
    if (!array->data) {
        array->data = malloc(sizeof(String));
    }

    array->data = realloc(array->data, (array->length + 1) * sizeof(String));
    array->data[array->length] = value;
    array->length++;
}

void pushNumberArray(NumberArray *array, Number value) {
    if (!array->data) {
        array->data = malloc(sizeof(Number));
    }

    array->data = realloc(array->data, (array->length + 1) * sizeof(Number));
    array->data[array->length] = value;
    array->length++;
}

void pushBoolArray(BoolArray *array, Bool value) {
    if (!array->data) {
        array->data = malloc(sizeof(Bool));
    }

    array->data = realloc(array->data, (array->length + 1) * sizeof(Bool));
    array->data[array->length] = value;
    array->length++;
}

void freeStringArray(StringArray *array) {
    free(array->data);
}

void freeNumberArray(NumberArray *array) {
    free(array->data);
}

void freeBoolArray(BoolArray *array) {
    free(array->data);
}