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