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

#include "foxqueue.h"
#include "foxbox.h"

#define NULL ((void*) 0)

FoxQueue FoxQueue_New() {
    FoxQueue fresh = {};
    fresh.start = -1;
    fresh.end = -1;
    fresh.size = 0;
    fresh.mem = FoxBox_New();

    return fresh;
}

int FoxQueue_Enqueue(FoxQueue *queue, void *item) {
    int res = FoxBox_PushFast(&queue->mem, item, queue->size);
    queue->end++;
    queue->size++;
    if (queue->size == 1) {
        queue->start = 0;
    }
    return res;
}

void *FoxQueue_Dequeue(FoxQueue *queue) {
    void *item = queue->mem[queue->start];
    queue->mem[queue->start] = NULL;
    queue->start++;
    if (queue->start == queue->size) {
        queue->start = -1;
        queue->end = -1;
        queue->size = 0;
    }
    return item;
}

void *FoxQueue_Start(FoxQueue queue) {
    return queue.mem[queue.end];
}

void *FoxQueue_End(FoxQueue queue) {
    return queue.mem[queue.end];
}

short FoxQueue_Empty(FoxQueue queue) {
    return queue.start == -1 && queue.end == -1 ? 1 : 0;
}

void FoxQueue_Swap(FoxQueue *main, FoxQueue *side) {
    FoxQueue temp = *main;
    *main = *side;
    *side = temp;
}

void FoxQueue_Free(FoxQueue *queue) {
    FoxBox_Clear(&queue->mem);
}