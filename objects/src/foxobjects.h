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

#ifndef FOXOBJECTS_H
#define FOXOBJECTS_H

// FoxObject is a struct that will be used to store the variables and methods, behaving like a class.

typedef struct {
    void **variables;
    char **varNames;
    unsigned short lastVar;
    void *(**methods)();
    char **methodNames;
    unsigned short lastMethod;
} FoxObject;

// A macro that is used to get the variable from the FoxObject, and cast it to the type given.
#define FoxObjects_getVariableU(class, name, type) (type) FoxObjects_getVariable(class, name)
// A macro that is used to call the method from the FoxObject, and cast it to the type given.
#define FoxObjects_callMethodU(class, name, args, type) (type) FoxObjects_callMethod(class, name, args)

// Initializing an FoxObject.
FoxObject FoxObjects_initObject(const void *constructor, const void *deconstructor, void **args);
// Creating a new FoxObject, and copying the parent's variables and methods into it.
FoxObject FoxObjects_inheritObject(FoxObject parent, void **args);
// Calling the deconstructor of the FoxObject.
void FoxObjects_removeObject(FoxObject *obj, void **args);

// A function that returns the index of the element in the array that has the same name as the name given.
int FoxObjects_getIndex(char **arr, const char *name, int size);

// Adding a variable to the FoxObject.
void FoxObjects_addVariable(FoxObject *obj, char *name, void *value);
// Getting the variable from the FoxObject.
void *FoxObjects_getVariable(FoxObject obj, const char *name);
// Setting the variable of the FoxObject to the value given.
void FoxObjects_setVariable(FoxObject *obj, const char *name, void *value);

// Adding a method to the FoxObject.
void FoxObjects_addMethod(FoxObject *obj, char *name, void *function);
// Calling the method of the FoxObject.
void *FoxObjects_callMethod(FoxObject obj, const char *name, void **args);
// Setting the method of the FoxObject to the function given.
void FoxObjects_setMethod(FoxObject *obj, const char *name, void *function);

#endif
