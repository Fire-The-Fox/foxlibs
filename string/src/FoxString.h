#ifndef FOXSTRING_H
#define FOXSTRING_H

enum FoxString_Signals {
    NOT_FOUND = -1,
    NO_ISSUE = 0,
    OUT_OF_MEMORY = 2,
    NO_LIMIT = 0,
    EQUAL = 1,
    NOT_EQUAL = 0,
    NOT_CREATED = 3
};

typedef struct {
    char *data;
    unsigned long size;
} FoxString;

// It creates a new FoxString with the given `init` string.
FoxString FoxString_New(const char *init);

// Cleaning the FoxString.
void FoxString_Clean(FoxString *string);

// Recreating the FoxString with the given `init` string.
FoxString FoxString_ReCreate(FoxString *string, const char *init);

// Reading a string from the standard input and returning it as a `FoxString`.
FoxString FoxStringInput();

// Counting the number of characters in the FoxString.
int FoxString_Count(FoxString string, char detect);

// Finding the first occurrence of the character in the FoxString.
int FoxString_Find(FoxString string, char detect);

// Checking if the `FoxString` contains the given `FoxString`.
int FoxString_Contains(FoxString str1, FoxString str2);

// Adding a character to the end of the FoxString.
int FoxString_Add(FoxString* string, char character);

// Removing the last character from the string and returning it.
char FoxString_Pop(FoxString* string);

// Connecting the `mainString` with the `sideString` together.
int FoxString_Connect(FoxString* mainString, FoxString sideString);

// Replacing the `oldChar` with the `newChar` in the `FoxString` `count` times.
FoxString FoxString_Replace(FoxString string, char oldChar, char newChar, int count);

// Comparing the two FoxStrings.
int FoxString_Compare(FoxString str1, FoxString str2);

#endif
