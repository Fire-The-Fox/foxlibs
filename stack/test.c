#include <stdio.h>

#include "foxstack.h"

int main() {
    FoxStack stack = FoxStack_New();
    int arr[] = {8, 1, 9};
    int *ptr = arr;
    FoxStack_Push(&stack, ptr);
    ptr++;
    FoxStack_Push(&stack, ptr);
    ptr++;
    FoxStack_Push(&stack, ptr);

    printf("%d\n", *(int*) FoxStack_Top(stack));
    printf("%d\n", *(int*) FoxStack_Pop(&stack));
    printf("%d\n", *(int*) FoxStack_Top(stack));

    ptr--;
    ptr--;
    
    FoxStack_Push(&stack, ptr);

    printf("%d\n", *(int*) FoxStack_Pop(&stack));

    return 0;
}