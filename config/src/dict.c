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