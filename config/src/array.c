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