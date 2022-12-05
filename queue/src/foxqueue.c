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

#ifdef FOXQUEUE_NORMAL

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
    return queue.mem[queue.start];
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

#endif
#ifdef FOXQUEUE_CIRCULAR

FoxCircularQueue FoxCircularQueue_New() {
    FoxCircularQueue fresh = {};
    fresh.start = -1;
    fresh.end = -1;
    fresh.size = 0;
    fresh.halted = 0;
    fresh.mem = FoxBox_New();

    return fresh;
}

int FoxCircularQueue_Enqueue(FoxCircularQueue *queue, void *item) {
    if (!queue->halted) {
        int res = FoxBox_PushFast(&queue->mem, item, queue->size);
        queue->end++;
        queue->size++;
        if (queue->size == 1) {
            queue->start = 0;
        }
        return res;
    }

    queue->end++;
    if (queue->end == queue->start) {
        queue->end--;
        return -1;
    }

    if (queue->end == queue->size) {
        if (queue->start > 0)
            queue->end = 0;
        else
            queue->end--;
    }

    queue->mem[queue->end] = item;
    return 0;
}

void *FoxCircularQueue_Dequeue(FoxCircularQueue *queue) {
    void *item = queue->mem[queue->start];
    queue->mem[queue->start] = NULL;
    queue->start++;
    if (queue->start == queue->size) {
        if (queue->end > 0)
            queue->start = 0;
        else
            queue->start--;
    }
    return item;
}
void *FoxCircularQueue_Start(FoxCircularQueue queue) {
    return queue.mem[queue.start];
}

void *FoxCircularQueue_End(FoxCircularQueue queue) {
    return queue.mem[queue.end];
}

short FoxCircularQueue_Empty(FoxCircularQueue queue) {
    for (int i = 0; i < queue.size; i++)
        if (queue.mem[i])
            return 0;
    return 1;
}

short FoxCircularQueue_Full(FoxCircularQueue queue) {
    for (int i = 0; i < queue.size; i++)
        if (!queue.mem[i])
            return 0;
    return 1;
}

void FoxCircularQueue_Halt(FoxCircularQueue *queue) {
    if (queue->halted)
        queue->halted--;
    else
        queue->halted++;
}

void FoxCircularQueue_Swap(FoxCircularQueue *main, FoxCircularQueue *side) {
    FoxCircularQueue temp = *main;
    *main = *side;
    *side = temp;
}

void FoxCircularQueue_Free(FoxCircularQueue *queue) {
    FoxBox_Clear(&queue->mem);   
}
#endif