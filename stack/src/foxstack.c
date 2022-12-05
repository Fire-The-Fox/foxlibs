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

#include "foxstack.h"
#include "foxbox.h"

FoxStack FoxStack_New() {
    FoxStack fresh = {};
    fresh.top = -1;
    fresh.size = 0;
    fresh.mem = FoxBox_New();
    return fresh;
}

int FoxStack_Push(FoxStack *stack, void* item) {
    int ret = FoxBox_PushFast(&stack->mem, item, stack->size);
    stack->size++;
    stack->top++;
    return ret;
}
void* FoxStack_Pop(FoxStack *stack) {
    void *item = FoxBox_PopFast(&stack->mem, stack->size);
    stack->size--;
    stack->top--;
    return item;
}

void* FoxStack_Top(FoxStack stack) {
    return stack.mem[stack.top];
}

short FoxStack_Empty(FoxStack stack) {
    return stack.top == -1 ? 1 : 0;
}

void FoxStack_Swap(FoxStack *main, FoxStack *side) {
    FoxStack temp = *main;
    *main = *side;
    *side = temp;
}

void FoxStack_Free(FoxStack *stack) {
    FoxBox_Free(stack->mem);
}