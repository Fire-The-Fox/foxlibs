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
