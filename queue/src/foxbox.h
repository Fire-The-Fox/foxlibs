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

#ifndef FOXBOX_H
#define FOXBOX_H

typedef void **FoxBox;

FoxBox FoxBox_New();

int FoxBox_Push(FoxBox *box, void *item);
int FoxBox_PushFast(FoxBox *box, void *item, int size);

void *FoxBox_Pop(FoxBox *box);
void *FoxBox_PopFast(FoxBox *box, int size);

int FoxBox_Fill(FoxBox *box, int count, void *item);

void *FoxBox_Erase(FoxBox *box, int index);
void *FoxBox_EraseFast(FoxBox *box, int index, int size);

int FoxBox_Insert(FoxBox *box, int index, void *value);
int FoxBox_InsertFast(FoxBox *box, int index, void *value, int size);

void FoxBox_Swap(FoxBox *main, FoxBox *side);
int FoxBox_Clear(FoxBox *box);

unsigned int FoxBox_Size(FoxBox box);
void FoxBox_Free(FoxBox box);

#endif
