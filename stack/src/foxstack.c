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