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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <linux/limits.h>
#include <libgen.h>

#include "parser.h"
#include "dict.h"
#include "types.h"
#include "array.h"

char *joinStringArray(StringArray *array, char *separator) {
    char *result = malloc(1);
    result[0] = '\0';
    for (int i = 0; i < array->length; i++) {
        result = realloc(result, strlen(result) + strlen(array->data[i]) + strlen(separator) + 1);
        strcat(result, array->data[i]);
        if (i != array->length - 1) {
            strcat(result, separator);
        }
    }
    return result;
}

void popStringArray(StringArray *array) {
    array->length--;
    array->data = realloc(array->data, array->length * sizeof(char *));
}

short contains(char *line, char *detect) {
    if (strstr(line, detect)) {
        return 1;
    }
    return 0;
}

char *trim(char *buff)
{
    while(1) {
        if(isspace(*buff)) { 
                ++buff;
        } else
            break;
    }

    int y = strlen(buff) - 1;
    while(1) {
        if(isspace(buff[y])) y--;
        else break;
    }
    y = strlen(buff) - y;
    buff[strlen(buff) - y + 1] = '\0';
    return buff;
}

char *trimStr(char *str) {
    char *result = malloc(strlen(str) - 1);
    strncpy(result, str + 1, strlen(str) - 2);
    result[strlen(str) - 2] = '\0';
    return result;
}

void parse(char *filename, Dict *dict) {
    if (dict->imported) {
        for (int i = 0; i < dict->importedLength; i++) {
            if (strcmp(dict->imported[i], filename) == 0) {
                return;
            }
        }
    }
    
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Error: File not found: %s\n", filename);
        exit(1);
    }

    if (!dict->imported) {
        dict->imported = (char**) malloc(sizeof(char*));
    }
    
    dict->imported = realloc(dict->imported, (dict->importedLength + 1) * sizeof(char*));
    dict->imported[dict->importedLength] = filename;
    dict->importedLength++;

    char temp = 50;
    unsigned int size;
    StringArray config_base = newStringArray();
    Bool in_special = 0;

    while (temp != EOF) {
        temp = fgetc(file);
        if (temp == '\n') continue;

        char *line = (char*) malloc(1);
        char *trimed;
        char *token;
        size = 1;

        while (temp > '\n') {
            line = realloc(line, size + 1);
            line[size-1] = temp;
            line[size] = '\0';
            temp = fgetc(file);
            size++;
        }

        trimed = trim(line);
        if (trimed[0] == '#') continue;

        if (contains(trimed, "=")) {
            token = trim(strtok_r(trimed, "=", &trimed));
            DictMember temp;
            if (in_special) {
                // join strings in array to one string with .
                char *joined = joinStringArray(&config_base, ".");
                char *result = malloc(strlen(joined) + strlen(token) + 2);
                strcpy(result, joined);
                strcat(result, ".");
                strcat(result, token);
                temp = getFromDict(*dict, result);
                free(result);
            } else {
                temp = getFromDict(*dict, token);
            }
            trimed = trim(trimed);
            switch (temp.type) {
                case Number_type:
                    *(Number*) temp.var = atoi(trimed);
                    break;
                case String_type:
                    if (trimed[0] != '"') {
                        fprintf(stderr, "Error: String must be in \"\".");
                        exit(1);
                    }
                    token = strtok_r(trimed, "\"", &trimed);
                    *(String*) temp.var = malloc(strlen(token) + 1);
                    strcpy(*(String*) temp.var, token);
                    break;
                case Bool_type:
                    if (strcmp(trimed, "true") == 0) {
                        *(Bool*) temp.var = 1;
                    } else if (strcmp(trimed, "false") == 0) {
                        *(Bool*) temp.var = 0;
                    } else {
                        fprintf(stderr, "Error: Bool must be true or false.");
                        exit(1);
                    }
                    break;
                case StringArray_type:
                    if (trimed[0] != '[') {
                        fprintf(stderr, "Error: StringArray must be in [].");
                        exit(1);
                    }
                    token = strtok_r(trimed+1, "]", &trimed);
                    StringArray *array = (StringArray*) temp.var;
                    *array = newStringArray();

                    token = strtok(token, ",");

                    while (token != NULL) {
                        token = trim(token);
                        if (token[0] != '"') {
                            fprintf(stderr, "Error: String must be in \"\".");
                            exit(1);
                        }
                        token = trimStr(token);
                        pushStringArray(array, token);
                        token = strtok(NULL, ",");
                    }
                    break;
                case NumberArray_type:
                    if (trimed[0] != '[') {
                        fprintf(stderr, "Error: NumberArray must be in [].");
                        exit(1);
                    }
                    token = strtok_r(trimed+1, "]", &trimed);
                    NumberArray *array2 = (NumberArray*) temp.var;
                    *array2 = newNumberArray();

                    token = strtok(token, ",");

                    while (token != NULL) {
                        token = trim(token);
                        pushNumberArray(array2, atoi(token));
                        token = strtok(NULL, ",");
                    }
                    break;
                case BoolArray_type:
                    if (trimed[0] != '[') {
                        fprintf(stderr, "Error: BoolArray must be in [].");
                        exit(1);
                    }
                    token = strtok_r(trimed+1, "]", &trimed);
                    BoolArray *array3 = (BoolArray*) temp.var;
                    *array3 = newBoolArray();

                    token = strtok(token, ",");

                    while (token != NULL) {
                        token = trim(token);
                        if (strcmp(token, "true") == 0) {
                            pushBoolArray(array3, 1);
                        } else if (strcmp(token, "false") == 0) {
                            pushBoolArray(array3, 0);
                        } else {
                            fprintf(stderr, "Error: Bool must be true or false.");
                            exit(1);
                        }
                        token = strtok(NULL, ",");
                    }
                    break;
                case None_type:
                    break;
            }
        } else if (contains(trimed, "{")) {
            in_special++;
            token = trim(strtok_r(trimed, "{", &trimed));
            char *copy = malloc(strlen(token) + 1);
            strcpy(copy, token);
            pushStringArray(&config_base, copy);
        } else if (contains(trimed, "}")) {
            in_special--;
            if (in_special < 0) {
                fprintf(stderr, "Error: Too many }.");
                exit(1);
            }
            popStringArray(&config_base);
        } else if (contains(trimed, "include")) {
            token = trim(strtok(trimed, "\""));
            token = trim(strtok(NULL, "\""));
            char *temp_path = realpath(filename, NULL);
            if (temp_path == NULL) {
                fprintf(stderr, "Error: File %s not found.\n", token);
                exit(1);
            }
            char *dir = dirname(temp_path);
            char *path = malloc(strlen(dir) + strlen(token) + 2);
            strcpy(path, dir);
            strcat(path, "/");
            strcat(path, token);
            free(temp_path);
            parse(path, dict);
        }
        free(line);
    }
    fclose(file);
}