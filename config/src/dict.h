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

#ifndef DICT_H
#define DICT_H

#include "types.h"

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

#endif