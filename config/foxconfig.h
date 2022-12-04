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

#ifndef FOXCONFIG_H
#define FOXCONFIG_H

enum Types {
    None_type = -1,
    String_type,
    StringArray_type,
    Number_type,
    NumberArray_type,
    Bool_type,
    BoolArray_type
};

typedef char Bool;

typedef char* String;

typedef int Number;

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

void freeStringArray(StringArray *array);
void freeNumberArray(NumberArray *array);
void freeBoolArray(BoolArray *array);

typedef struct {
    char *key;
    enum Types type;
    void* var;
} DictMember;

typedef struct {
    DictMember *members;
    unsigned int length;
    char **imported;
    unsigned int importedLength;
} Dict;

Dict newDict();
void assingDict(Dict *dict, char *key, enum Types type, void *var);
DictMember getFromDict(Dict dict, char *key);
void freeDict(Dict *dict);

void parse(char *filename, Dict *dict);

#endif
