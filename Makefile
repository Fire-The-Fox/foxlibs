include .config

LIB_BUNDLE = 
HEADERS = 

.DEFAULT_GOAL = help

ifeq ($(CONFIG_FOXCONFIG), y)

	LIB_BUNDLE += ./config/libfoxconfig.a
	HEADERS += ./config/foxconfig.h

endif
ifeq ($(CONFIG_FOXSTRING), y)

	LIB_BUNDLE += ./string/libfoxstring.a
	HEADERS += ./string/foxstring.h

endif
ifeq ($(CONFIG_FOXOBJECTS), y)

	LIB_BUNDLE += ./objects/libfoxobjects.a
	HEADERS += ./objects/foxobjects.h

endif

defconfig:
	@cd kconfig-frontends && ./bootstrap
	@cd kconfig-frontends && ./configure --disable-{nconf,gconf,qconf,conf}
	$(MAKE) kconfig-frontends

menuconfig:
	./kconfig-frontends/frontends/mconf/mconf Kconfig

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
	ar rcs ./libfoxlibs.a $(LIB_BUNDLE)
	cat $(HEADERS) > libfoxlibs.h

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
	rm ./libfoxlibs.a
	rm libfoxlibs.h