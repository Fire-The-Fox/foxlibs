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

#ifndef FOXSTACK_H
#define FOXSTACK_H

#include "foxbox.h"

typedef struct {
    int top;
    int size;
    FoxBox mem;
} FoxStack;

FoxStack FoxStack_New();

int FoxStack_Push(FoxStack *stack, void* item);
void* FoxStack_Pop(FoxStack *stack);
void* FoxStack_Top(FoxStack stack);
short FoxStack_Empty(FoxStack stack);
void FoxStack_Swap(FoxStack *main, FoxStack *side);
void FoxStack_Free(FoxStack *stack);

#endif