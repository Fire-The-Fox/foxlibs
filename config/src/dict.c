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
#include <string.h>

#include "dict.h"

Dict newDict() {
    Dict dict;
    dict.members = NULL;
    dict.length = 0;
    dict.imported = NULL;
    dict.importedLength = 0;
    return dict;
}

void assingDict(Dict *dict, char *key, enum Types type, void *var) {
    if (!dict->members) {
        dict->members = malloc(sizeof(DictMember));
    }

    dict->members = realloc(dict->members, (dict->length + 1) * sizeof(DictMember));
    dict->members[dict->length].key = key;
    dict->members[dict->length].type = type;
    dict->members[dict->length].var = var;
    dict->length++;
}

DictMember getFromDict(Dict dict, char *key) {
    DictMember member;
    member.type = None_type;
    
    for (int i = 0; i < dict.length; i++) {
        if (strcmp(dict.members[i].key, key) == 0) {
            member.type = dict.members[i].type;
            member.var = dict.members[i].var;
            break;
        }
    }

    return member;
}

void freeDict(Dict *dict) {
    free(dict->members);
}