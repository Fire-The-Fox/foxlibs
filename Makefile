defconfig:
	@cd kconfig-frontends && ./bootstrap
	@cd kconfig-frontends && ./configure --disable-{nconf,gconf,qconf,conf}
	$(MAKE) kconfig-frontends
