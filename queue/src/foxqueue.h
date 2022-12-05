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

#ifndef FOXQUEUE_H
#define FOXQUEUE_H

#include "foxbox.h"

typedef struct {
    int start;
    int end;
    int size;
    FoxBox mem;
} FoxQueue;

FoxQueue FoxQueue_New();

int FoxQueue_Enqueue(FoxQueue *queue, void *item);
void *FoxQueue_Dequeue(FoxQueue *queue);
void *FoxQueue_Start(FoxQueue queue);
void *FoxQueue_End(FoxQueue queue);
short FoxQueue_Empty(FoxQueue queue);
void FoxQueue_Swap(FoxQueue *main, FoxQueue *side);
void FoxQueue_Free(FoxQueue *queue);

typedef struct {
    int start;
    int end;
    int size;
    short halted;
    FoxBox mem;
} FoxCircularQueue;

FoxCircularQueue FoxCircularQueue_New();

int FoxCircularQueue_Enqueue(FoxCircularQueue *queue, void *item);
void *FoxCircularQueue_Dequeue(FoxCircularQueue *queue);
void *FoxCircularQueue_Start(FoxCircularQueue queue);
void *FoxCircularQueue_End(FoxCircularQueue queue);
short FoxCircularQueue_Empty(FoxCircularQueue queue);
short FoxCircularQueue_Full(FoxCircularQueue queue);
void FoxCircularQueue_Halt(FoxCircularQueue *queue);
void FoxCircularQueue_Swap(FoxCircularQueue *main, FoxCircularQueue *side);
void FoxCircularQueue_Free(FoxCircularQueue *queue);

#endif