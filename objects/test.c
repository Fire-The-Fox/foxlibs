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
#include <string.h>
#include <stdlib.h>

#include "foxobjects.h"

typedef FoxObject Animal;
typedef Animal Hybrid;

/* A constructor for the Animal FoxObject. */
void Animal_constructor(Animal *this);
/* A deconstructor for the Animal FoxObject. It is called when the FoxObject is removed. */
void Animal_deconstructor();
/* Creating a new Animal FoxObject. */
Animal Animal_New();

/* Creating a new FoxObject that inherits from the Animal FoxObject. */
Hybrid Hybrid_New(Animal parent);
/* A method that is called when the `sound` method is called on the FoxObject. */
void Hybrid_Say(const Hybrid *this);

int test_fun(const FoxObject *this);

int main() {
    /* Creating a new Animal FoxObject and assigning it to the variable `AnimalTemplate`. */
    Animal AnimalTemplate = Animal_New();

    /* Creating two new FoxObjects that inherit from the Animal FoxObject. */
    Hybrid dog = Hybrid_New(AnimalTemplate);
    Hybrid cat = Hybrid_New(AnimalTemplate);

    /* Setting the variables of the FoxObjects. */
    FoxObjects_setVariable(&dog, "type", "Dog");
    FoxObjects_setVariable(&dog, "sound", "Bark");
    FoxObjects_setVariable(&cat, "type", "Cat");
    FoxObjects_setVariable(&cat, "sound", "Meow");

    /* Calling the `sound` method on the `dog` and `cat` FoxObject. */
    FoxObjects_callMethod(dog, "sound", NULL);
    FoxObjects_callMethod(cat, "sound", NULL);

    /* Removing the FoxObjects from memory. */
    FoxObjects_removeObject(&dog, NULL);
    FoxObjects_removeObject(&cat, NULL);
    FoxObjects_removeObject(&AnimalTemplate, NULL);
    
    FoxObject test = FoxObjects_initObject(NULL, NULL, NULL);
    int cislo = 777;
    FoxObjects_addVariable(&test, "cislo", &cislo);
    FoxObjects_addMethod(&test, "fun", &test_fun);
    
	printf("\nMethod call returned: %d\n", FoxObjects_callMethodU(test, "fun", NULL, int*));
    
    FoxObjects_removeObject(&test, NULL);

    return 0;
}

void Animal_constructor(Animal *this) {
    FoxObjects_addVariable(this, "sound", "Animal sound");
}

void Animal_deconstructor() {
    printf("Executing deconstructor\n");
}

Animal Animal_New() {
    return FoxObjects_initObject(&Animal_constructor, &Animal_deconstructor, NULL);
}

Hybrid Hybrid_New(Animal parent) {
    Hybrid inherit = FoxObjects_inheritObject(parent, parent.variables);
    FoxObjects_addMethod(&inherit, "sound", &Hybrid_Say);
    FoxObjects_addVariable(&inherit, "type", "Hybrid");
    return inherit;
}

void Hybrid_Say(const Hybrid *this) {
    printf("%s says: %s\n", FoxObjects_getVariableU(*this, "type", char*), FoxObjects_getVariableU(*this, "sound", char*));
}

int test_fun(const FoxObject *this) {
	return *FoxObjects_getVariableU(*this, "cislo", int*);
}