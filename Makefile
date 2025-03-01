__OS 			 := $(shell \
. `pwd`/sh/envs.sh; printenv __OS)
LIB_EXT 		 := $(shell \
. `pwd`/sh/envs.sh; printenv LIB_EXT)
LIBGCC_DIRECTORY := $(shell \
. `pwd`/sh/envs.sh; printenv LIBGCC_DIRECTORY)
export __OS
export LIB_EXT
export LIBGCC_DIRECTORY

# Inputs (default values)
debug := 0
install_directory := $(shell pwd)


.PHONY: all clean default add_to_env build test
all: default

default: build test clean

add_to_env:
	. `pwd`/sh/reg.sh

build:
	cd src && pwd; \
	make -f Makefile install_directory=$(install_directory) debug=$(debug);

test:
	cd tests && pwd; \
	make -f Makefile install_directory=$(install_directory);

clean:
	cd src && pwd; \
	make -f Makefile clean;
	cd tests && pwd; \
	make -f Makefile clean;
