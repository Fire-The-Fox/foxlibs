#include <stdio.h>

#include "foxconfig.h"

struct nested {
    String name;
};

typedef struct {
    Number val;
    String name;
    Bool bul;
    StringArray vtubers;
    NumberArray numbers;
    BoolArray bools;
    struct nested nest;
} config;

int main(int argc, char *argv[]) {
    Dict dict = newDict();
    config config;
    
    assingDict(&dict, "config.val", Number_type, &config.val);
    assingDict(&dict, "config.name", String_type, &config.name);
    assingDict(&dict, "config.bul", Bool_type, &config.bul);
    assingDict(&dict, "config.fav_vtubers", StringArray_type, &config.vtubers);
    assingDict(&dict, "config.numbers", NumberArray_type, &config.numbers);
    assingDict(&dict, "config.bools", BoolArray_type, &config.bools);
    assingDict(&dict, "config.nest.name", String_type, &config.nest.name);

    parse(argv[1], &dict);

    printf("%d\n", config.val);
    printf("%s\n", config.name);
    printf("%d\n\nArray content:\n", config.bul);

    for (int i = 0; i < config.vtubers.length; i++) {
        printf("%s\n", config.vtubers.data[i]);
    }
    
    printf("\nArray content:\n");
    for (int i = 0; i < config.numbers.length; i++) {
        printf("%d\n", config.numbers.data[i]);
    }

    printf("\nArray content:\n");
    for (int i = 0; i < config.bools.length; i++) {
        printf("%s\n", config.bools.data[i] ? "true" : "false");
    }

    printf("\nNested struct content:\n");
    printf("%s\n", config.nest.name);

    freeDict(&dict);
    return 0;
}