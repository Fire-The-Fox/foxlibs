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

include .config

LIB_BUNDLE = 
HEADERS = 

.DEFAULT_GOAL = help

ifeq ($(CONFIG_FOXCONFIG), y)

	LIB_BUNDLE += ../config/libfoxconfig.a
	HEADERS += ./config/foxconfig.h

endif
ifeq ($(CONFIG_FOXSTRING), y)

	LIB_BUNDLE += ../string/libfoxstring.a
	HEADERS += ./string/foxstring.h

endif
ifeq ($(CONFIG_FOXOBJECTS), y)

	LIB_BUNDLE += ../objects/libfoxobjects.a
	HEADERS += ./objects/foxobjects.h

endif
ifeq ($(CONFIG_FOXBOX), y)

	LIB_BUNDLE += ../box/libfoxbox.a
	HEADERS += ./box/foxbox.h

endif
ifeq ($(CONFIG_FOXSTACK), y)

	LIB_BUNDLE += ../stack/libfoxstack.a
	HEADERS += ./stack/foxstack.h

endif

ifeq ($(CONFIG_FOXQUEUES), y)

export CONFIG_FOXQUEUE_NORMAL

	LIB_BUNDLE += ../queue/libfoxqueue.a
	HEADERS += ./queue/foxqueue.h

endif

defconfig:
	@cd kconfig-frontends && ./bootstrap
	@cd kconfig-frontends && ./configure --disable-{nconf,gconf,qconf,conf}
	$(MAKE) kconfig-frontends

menuconfig:
	./kconfig-frontends/frontends/mconf/mconf KConfig

help:
	@echo "'make defconfig' to create configuration"
	@echo "'make menuconfig' to launch configuration menu"
	@echo "'make all' to compile using the config"
	@echo "'make clean' to clean the directory"

all:
ifeq ($(CONFIG_FOXCONFIG), y)
	$(MAKE) -C config all
endif
ifeq ($(CONFIG_FOXSTRING), y)
	$(MAKE) -C string all
endif
ifeq ($(CONFIG_FOXOBJECTS), y)
	$(MAKE) -C objects all
endif
ifeq ($(CONFIG_FOXBOX), y)
	$(MAKE) -C box all
endif
ifeq ($(CONFIG_FOXSTACK), y)
	$(MAKE) -C stack all
endif
ifeq ($(CONFIG_FOXQUEUES), y)
	$(MAKE) -C queue all
endif

	mkdir -p extracted
	$(foreach lib, $(LIB_BUNDLE), cd extracted && ar x $(lib); cd ..;)
	ar rcs libfoxlibs.a extracted/*
	rm -rf extracted
	@cat $(HEADERS) > foxlibs.h | sed -i '/#include/d' foxlibs.h

clean:
ifeq ($(CONFIG_FOXCONFIG), y)
	$(MAKE) -C config clean
endif
ifeq ($(CONFIG_FOXSTRING), y)
	$(MAKE) -C string clean
endif
ifeq ($(CONFIG_FOXOBJECTS), y)
	$(MAKE) -C objects clean
endif
ifeq ($(CONFIG_FOXBOX), y)
	$(MAKE) -C box clean
endif
ifeq ($(CONFIG_FOXSTACK), y)
	$(MAKE) -C stack clean
endif
ifeq ($(CONFIG_FOXQUEUES), y)
	$(MAKE) -C stack clean
endif

	rm ./libfoxlibs.a
	rm foxlibs.h