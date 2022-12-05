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

#include "foxstring.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


FoxString
FoxString_New(const char *init)
{
    FoxString new;

    if (init == NULL || strcmp(init, "\0") == 0) {

        new.data = (char*) malloc(1);
        *(new.data+0) = '\0';
        new.size = 0;

    } else {

        new.data = (char*) malloc(strlen(init)+1);
        strcpy(new.data, init);
        new.size = strlen(new.data);
    }
    return new;
}


void
FoxString_Clean(FoxString *string)
{
    free(string->data);
    string->size = 0;
}

FoxString
FoxString_ReCreate(FoxString *string, const char *init)
{
    FoxString_Clean(string);

    FoxString fresh = FoxString_New(init);

    return fresh;
}

FoxString
FoxStringInput()
{
    int bufferChar;
    FoxString string = FoxString_New(NULL);

    while(true) {
        bufferChar = getchar();
        if (bufferChar == '\n') break;
        FoxString_Add(&string, (char) bufferChar);
    }

    return string;
}

int
FoxString_Count(FoxString string, char detect)
{
    int found = 0;

    for (int i = 0; i < strlen(string.data); i++) {
        if (string.data[i] == detect) found++;
    }

    return found;
}

int
FoxString_Find(FoxString string, char detect)
{
    int i;

    for (i = 0; i < strlen(string.data); i++) {
        if (string.data[i] == detect) break;
    }

    if (i < strlen(string.data)) return i;
    else return NOT_FOUND;
}

int
FoxString_Contains(FoxString str1, FoxString str2)
{
    short found = false;

    if (strstr(str1.data, str2.data)) found = true;

    return found;
}

int
FoxString_Add(FoxString* string, char character)
{
    string->data = realloc(string->data, string->size + 2);

    if (string->data == NULL) return OUT_OF_MEMORY;

    string->data[string->size] = character;
    string->data[string->size + 1] = '\0';
    string->size = strlen(string->data);

    return NO_ISSUE;
}

int
FoxString_Connect(FoxString* mainString, FoxString sideString)
{
    mainString->data = realloc(mainString->data, mainString->size + sideString.size);

    if (mainString->data == NULL) return OUT_OF_MEMORY;

    strcat(mainString->data, sideString.data);
    mainString->size = strlen(mainString->data);

    return NO_ISSUE;
}

char
FoxString_Pop(FoxString* string)
{
    char beforePop = string->data[string->size-1];
    
    string->data[string->size-1] = '\0';
    string->size--;
    string->data = realloc(string->data, string->size);

    return beforePop;
}


FoxString
FoxString_Replace(FoxString string, char oldChar, char newChar, int count)
{
    FoxString fresh = FoxString_New(NULL);
    int replacements = 0;

    if (count == NO_LIMIT) count = (int) strlen(string.data);

    for (int i = 0; i < strlen(string.data); i++) {
        if (string.data[i] == oldChar && newChar != '\0' && replacements < count) {
            replacements++;
            FoxString_Add(&fresh, newChar);
        } else if (string.data[i] == oldChar && newChar == '\0' && replacements < count) {
            i++;
            replacements++;
            FoxString_Add(&fresh, string.data[i]);
        } else FoxString_Add(&fresh, string.data[i]);
    }

    return fresh;
}

int
FoxString_Compare(FoxString str1, FoxString str2)
{
    if (strcmp(str1.data, str2.data) == 0) return EQUAL;
    return NOT_EQUAL;
}
