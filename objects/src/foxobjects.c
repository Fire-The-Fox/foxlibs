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

#include "foxobjects.h"

#include <stdlib.h>
#include <string.h>

FoxObject FoxObjects_initObject(const void *constructor, const void *deconstructor, void **args) {
    FoxObject obj;

    /* Allocating memory for the methods array. */
    obj.methods = malloc(sizeof(void*) * 2);

    /* Making sure constructor and deconstructor won't have garbage values from malloc. */
    obj.methods[0] = NULL;
    obj.methods[1] = NULL;

    /* Size of how many methods are in methods array. */
    obj.lastMethod = 2;
    obj.lastVar = 0;

    /* Casting the pointer to a char pointer, then casting it back to a char double pointer. */
    obj.methodNames = (char **) malloc(sizeof(char**) * obj.lastMethod);

    /* Allocating memory for the method names, and copying the names into the memory. */
    obj.methodNames[0] = (char*) malloc(11);
    memcpy(obj.methodNames[0], "constructor", 11);
    obj.methodNames[1] = (char*) malloc(13);
    memcpy(obj.methodNames[1], "deconstructor", 13);

    /* Checking if the constructor is not null, and if it is not, it sets the constructor to the first method in the
    methods array, and then calls the constructor. */
    if (constructor != NULL) {
        obj.methods[0] = constructor;
        obj.methods[0](&obj, args);
    } else obj.methods[0] = NULL;

    /* Checking if the deconstructor is not null, and if it is not, it sets the deconstructor to the second method in the
    methods array. */
    if (deconstructor != NULL) obj.methods[1] = deconstructor;
    else obj.methods[1] = NULL;

    return obj;
}

FoxObject FoxObjects_inheritObject(FoxObject parent, void **args) {
    FoxObject inherited;

    /* Allocating memory for the methods and variables arrays, and then setting the first method to null for removing garbage
    value. */
    inherited.methods = malloc(sizeof(void*) * parent.lastMethod);
    inherited.variables = malloc(sizeof(void**) * parent.lastVar);
    inherited.methods[0] = NULL;

    /* Allocating memory for the method and variable names. */
    inherited.methodNames = (char **) malloc(sizeof(char**) * parent.lastMethod);
    inherited.varNames = (char **) malloc(sizeof(char**) * parent.lastVar);

    /* Size of how many methods are in methods array. */
    inherited.lastMethod = parent.lastMethod;
    inherited.lastVar = 0;

    /* Copying the methods and method names from the parent FoxObject to the inherited FoxObject. */
    for (int i = 0; i < parent.lastMethod; i++) {
        inherited.methods[i] = parent.methods[i];

        inherited.methodNames[i] = malloc(sizeof(parent.methodNames[i]));
        strcpy(inherited.methodNames[i], parent.methodNames[i]);
    }

    /* Calling the constructor of the inherited FoxObject. */
    if (inherited.methods[0] != NULL) inherited.methods[0](&inherited, args);

    return inherited;
}

void FoxObjects_removeObject(FoxObject *obj, void **args) {
    /* Calling the deconstructor of the object. */
    if (obj->methods[1] != NULL){
    	obj->methods[1](*obj, args);
	}

    /* Freeing the memory that was allocated for the method names, variable names, methods, and variables. */
    free(obj->methodNames);
    free(obj->varNames);
    free(obj->methods);
    free(obj->variables);
}

void FoxObjects_addVariable(FoxObject *obj, char *name, void *value) {

    /* Checking if the FoxObject has any variables, and if it does, it reallocates the memory for the variables array. */
    if (obj->lastVar == 0) {
        obj->variables = malloc(sizeof(void **) * 1);
        obj->varNames = (char **) malloc(sizeof(char**) * 1);
        obj->lastVar++;
    } else {
        obj->lastVar++;
        obj->variables = (void**) realloc(obj->variables, obj->lastVar);
    }

    /* Setting the variable name and value to the last index of the variables array. */
    obj->varNames[obj->lastVar-1] = name;
    obj->variables[obj->lastVar-1] = value;
}

void *FoxObjects_getVariable(FoxObject obj, const char *name) {

    /* Getting the index of the variable name in the variable names array, and then using that index to get the variable
    from the variables array. */
    return obj.variables[FoxObjects_getIndex(obj.varNames, name, obj.lastVar)];
}

int FoxObjects_getIndex(char **arr, const char *name, int size) {
    int index;

    /* Getting the index of the variable name in the variable names array. */
    for (index = 0; index < size; index++) {
        if (!strcmp(arr[index], name)) {
            break;
        }
    }

    /* Checking if the index is equal to the size of the array, and if it is, it returns -1, otherwise it returns the
    index. */
    if (index == size) return -1;
    return index;
}

void FoxObjects_setVariable(FoxObject *obj, const char *name, void *value) {

    /* Getting the index of the variable name in the variable names array, and then using that index to set the variable
    in the variables array. */
    int index = FoxObjects_getIndex(obj->varNames, name, obj->lastVar);

    obj->variables[index] = value;
}

void FoxObjects_addMethod(FoxObject *obj, char *name, void *function) {

    obj->lastMethod++;
    /* Reallocating the memory for the methods array, and then casting it to a void pointer double pointer. */
    obj->methods = (void *(**)()) realloc(obj->methods, obj->lastMethod);

    /* Setting the method name and function to the last index of the methods array. */
    obj->methodNames[obj->lastMethod-1] = name;
    obj->methods[obj->lastMethod-1] = function;

}

void *FoxObjects_callMethod(FoxObject obj, const char *name, void **args) {

    /* Getting the index of the method name in the method names array, and then using that index to call the method
    from the methods array. */
    int index = FoxObjects_getIndex(obj.methodNames, name, obj.lastMethod);

    return obj.methods[index](&obj, args);
}

void FoxObjects_setMethod(FoxObject *obj, const char *name, void *function) {

    /* Getting the index of the method name in the method names array, and then using that index to set the method
    in the methods array. */
    int index = FoxObjects_getIndex(obj->methodNames, name, obj->lastMethod);

    obj->methods[index] = function;
}
