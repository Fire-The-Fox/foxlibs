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
#include "foxbox.h"

FoxBox FoxBox_New() {
    FoxBox fresh = malloc(sizeof(FoxBox));
    fresh[0] = NULL;
    return fresh;
}

int FoxBox_Push(FoxBox *box, void *item) {
    unsigned int size = FoxBox_Size(*box);
    size++;

    *box = realloc(*box, (size + 1) * sizeof(FoxBox));
    if (*box == NULL) return 1;
    else {
        *(*box+size - 1) = item;
        *(*box+size) = NULL;
        return 0;
    }
}

int FoxBox_PushFast(FoxBox *box, void *item, int size) {
    size++;
    *box = realloc(*box, (size + 1) * sizeof(FoxBox));

    if (*box == NULL) return 1;
    else {
        *(*box+size - 1) = item;
        *(*box+size) = NULL;
        return 0;
    }
}

void *FoxBox_Pop(FoxBox *box) {
    unsigned long size = FoxBox_Size(*box);
    void *item = (*box)[size - 1];

    *box = realloc(*box, (size + 1) * sizeof(FoxBox));
    
    if (*box == NULL) return NULL;
    else {
        *(*box+size - 1) = NULL;
        return item;
    }
}

void *FoxBox_PopFast(FoxBox *box, int size) {
    void *item = (*box)[size - 1];

    *box = realloc(*box, (size + 1) * sizeof(FoxBox));
    
    if (*box == NULL) return NULL;
    else {
        *(*box+size) = NULL;
        return item;
    }
}

int FoxBox_Fill(FoxBox *box, int count, void *item) {
    unsigned long size = FoxBox_Size(*box);
    
    for (int i = 0; i < count; i++) {

        int res = FoxBox_PushFast(box, item, size);

        if (res) {
            return 1;
        }

        size++;
    }
    return 0;
}

void *FoxBox_Erase(FoxBox *box, int index) {
    unsigned long size = FoxBox_Size(*box);
    void *item = (*box)[index];
    for (int i = index; i < size; i++) {
        (*box)[i] = (*box)[i + 1];
    }

    *box = realloc(*box, (size + 1) * sizeof(FoxBox));
    return item;
}

void *FoxBox_EraseFast(FoxBox *box, int index, int size) {
    void *item = (*box)[index];
    for (int i = index; i < size; i++) {
        (*box)[i] = (*box)[i + 1];
    }

    *box = realloc(*box, (size + 1) * sizeof(FoxBox));
    return item;
}

int FoxBox_Insert(FoxBox *box, int index, void *value) {
    unsigned long size = FoxBox_Size(*box);
    size++;

    (*box)[size + 1] = NULL;

    *box = realloc(*box, (size + 1) * sizeof(FoxBox));
    if (*box == NULL) return 1;

    for (int i = size; i > index; i--) {
        (*box)[i] = (*box)[i - 1];
    }

    (*box)[index] = value;

    return 0;
}
int FoxBox_InsertFast(FoxBox *box, int index, void *value, int size) {
    size++;

    (*box)[size] = NULL;

    *box = realloc(*box, (size + 2) * sizeof(FoxBox));
    if (*box == NULL) return 1;

    for (int i = size + 1; i > index; i--) {
        (*box)[i] = (*box)[i - 1];
    }

    (*box)[index] = value;

    return 0;
}

void FoxBox_Swap(FoxBox *main, FoxBox *side) {
    FoxBox temp = *main;
    *main = *side;
    *side = temp;
}

int FoxBox_Clear(FoxBox *box) {
    *box = realloc(*box, sizeof(FoxBox));
    if (*box == NULL) return 1;
    *box[0] = NULL;
    return 0;
}

unsigned int FoxBox_Size(FoxBox box) {
    int size;
    for (size = 0; box[size]; size++);
    return size;
}

void FoxBox_Free(FoxBox box) {
    free(box);
}