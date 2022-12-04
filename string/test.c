#include "foxstring.h"
#include <stdio.h>

int main(void)
{
    printf("Type something: ");

    FoxString string = FoxStringInput();
    printf("You entered: %s\n", string.data);

    FoxString_Clean(&string);

    // generate tests for FoxString
    FoxString new = FoxString_New("Hello, world");

    printf("The string is: %s\n", new.data);
    printf("The size is: %lu\n", new.size);
    printf("The count of 'l' in the string is: %d\n", FoxString_Count(new, 'l'));
    printf("The first 'l' is at: %d\n", FoxString_Find(new, 'l'));
    printf("Does the string contain 'world'? %s\n", FoxString_Contains(new, FoxString_New("world")) ? "Yes" : "No");
    printf("Does the string contain 'fox'? %s\n", FoxString_Contains(new, FoxString_New("fox")) ? "Yes" : "No");
    printf("The last character is: %c\n", FoxString_Pop(&new));
    printf("The string is: %s\n", new.data);
    printf("The size is: %lu\n", new.size);

    FoxString_Add(&new, 'd');
    printf("The string is: %s\n", new.data);
    printf("The size is: %lu\n", new.size);

    FoxString_Connect(&new, FoxString_New(" and fox"));
    printf("The string is: %s\n", new.data);
    printf("The size is: %lu\n", new.size);
    printf("Does the string contain 'fox'? %s\n", FoxString_Contains(new, FoxString_New("fox")) ? "Yes" : "No");

    FoxString replaced = FoxString_Replace(new, 'l', 'L', 2);

    printf("The string is: %s\n", replaced.data);
    printf("The size is: %lu\n", replaced.size);

    printf("Are the strings equal? %s\n", FoxString_Compare(new, replaced) ? "Yes" : "No");

    FoxString_Clean(&new);
    FoxString_Clean(&replaced);

    return 0;
}