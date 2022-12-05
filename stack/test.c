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