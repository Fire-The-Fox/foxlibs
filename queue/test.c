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
#include "foxqueue.h"

int main() {
    FoxQueue queue = FoxQueue_New();
    int arr[] = {1, 2, 3, 4, 5};
    int *ptr = arr;
    FoxQueue_Enqueue(&queue, ptr);
    ptr++;
    FoxQueue_Enqueue(&queue, ptr);
    ptr++;
    FoxQueue_Enqueue(&queue, ptr);
    ptr++;
    FoxQueue_Enqueue(&queue, ptr);
    ptr++;
    FoxQueue_Enqueue(&queue, ptr);

    void *removed = FoxQueue_Dequeue(&queue);

    for (int i = queue.start; i < queue.end + 1; i++) {
        printf("%d\n", *(int*) queue.mem[i]);
        FoxQueue_Dequeue(&queue);
    }

    printf("%d was removed\n", *(int*) removed);

    printf("Start: %d\nEnd: %d\nSize: %d\n", queue.start, queue.end, queue.size);
    printf("Why? FoxQueue is empty!\n");
    printf("Is FoxQueue empty? %s\n", FoxQueue_Empty(queue) ? "Yes" : "No");

    FoxQueue_Free(&queue);
    return 0;
}