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