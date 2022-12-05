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

#include "foxbox.h"
#include <stdio.h>

int main() {
    int arr[] = {9, 7, 5, 10};
    int *ptr = arr;

    FoxBox box = FoxBox_New();
    FoxBox box2 = FoxBox_New();

    int size = 0;
    FoxBox_PushFast(&box, ptr, size);
    ptr++;
    size++;

    FoxBox_PushFast(&box2, arr, 0);

    FoxBox_Push(&box, ptr);

    ptr++;

    FoxBox_Fill(&box, 6, ptr);
    size += 6;

    ptr++;
    FoxBox_Push(&box, ptr);

    void *poped = FoxBox_PopFast(&box, size);
    size--;

    for (int i = 0; i < size + 1; i++) {
        printf("%d\n", *(int*) box[i]);
    }

    printf("Poped: %d\n\n", *(int*) poped);

    FoxBox_EraseFast(&box, 0, size);
    size--;

    for (int i = 0; i < size + 1; i++) {
        printf("%d\n", *(int*) box[i]);
    }

    FoxBox_InsertFast(&box, 0, arr, size);
    size++;

    putchar(10);
    for (int i = 0; i < size + 1; i++) {
        printf("%d\n", *(int*) box[i]);
    }

    FoxBox_Swap(&box, &box2);

    printf("\nAfter swap\n");
    for (int i = 0; i < size + 1; i++) {
        printf("%d\n", *(int*) box2[i]);
    }

    FoxBox_Clear(&box);

    printf("Size of Cleared main box: %d\n", FoxBox_Size(box));

    return 0;
}