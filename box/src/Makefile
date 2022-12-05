# This file is part of foxlibs
# Copyright (C) 2022 Ján Gajdoš

# This library is free software: you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License as published
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.

# This library is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU Lesser General Public License for more details.

# You should have received a copy of the GNU Lesser General Public License
# along with this library.  If not, see <http://www.gnu.org/licenses/>.

CC ?= gcc
CFLAGS ?= -Wall -g -O2
OBJ = foxbox.o

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

all: $(OBJ)
	ar rcs ../libfoxbox.a $(OBJ)

clean:
	rm -f *.o
	rm -f ../libfoxbox.a