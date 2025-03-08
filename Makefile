# main makefile
#
#	@File:      Makefile
#	@Author:    Sam.Nazarov

# https://www.opennet.ru/docs/RUS/coding_standard/standard-5.html
SHELL=/bin/bash
$(shell ./sh/_env.sh `pwd`)
include _env
export _OS
export LIB_SUFFIX

# Inputs (default values)
coverage          = 0
debug             = 0
install_directory = $(shell pwd)
export coverage
export debug
export install_directory

.PHONY: all default build test clean debug
all: default

default: build test clean

build:
	cd src && pwd; \
	"$(MAKE)" -f Makefile

test:
	cd tests && pwd; \
	"$(MAKE)" -f Makefile

clean:
	cd src && pwd; \
	"$(MAKE)" -f Makefile clean;
	cd tests && pwd; \
	"$(MAKE)" -f Makefile clean;
	rm -rf $(install_directory)/check_cpathtools
	rm -rf _env;

debug:
	echo os: $(_OS);\
	echo ext: $(LIB_SUFFIX);
