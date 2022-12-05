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

#endif