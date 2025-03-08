# this makefile must not be included directly
#
#	@File:      Makefile
#	@Author:    Sam.Nazarov

SHELL   = /bin/bash
TARGET := libcpathtools.$(LIB_SUFFIX)

BUILD_DIR := ./build
SRC_DIRS  := 

SRCS := $(shell find $(SRC_DIRS) -name "*.c")
OBJS := $(SRCS:%.c=$(BUILD_DIR)/%.o)

CC := gcc

INCDIRS    	:= .
INCFLAGS   	:= $(addprefix -I,$(INCDIRS))
CDEBUGFLAGS := $(shell if [[ $(debug) == 1 ]]; then echo \
-g3 -O0 \
; else echo ; fi)
CDLLFLAGS   := $(shell if [[ $(_OS) == win ]]; then echo \
-DBUILDING_DLL \
; else echo ; fi)
# https://gcc.gnu.org/onlinedocs/gcc-14.2.0/gcc/Option-Summary.html
CFLAGS 	    := -Wall -Wextra -Wpedantic -Wshadow -Wformat=2 -Wcast-align \
-Wconversion -Wsign-conversion -Wnull-dereference -fdiagnostics-color=always \
-fvisibility=hidden -std=c99 -pedantic -fPIC -O2 $(INCFLAGS) $(CDLLFLAGS)
CGCOVFLAGS   = $(shell if [[ $(coverage) == 1 ]]; then echo \
-fprofile-arcs -ftest-coverage -fprofile-abs-path -O0 \
; else echo ; fi)

LIBDIRS    	:= 
LDFLAGS    	:= 
LDFLAGS    	+= -shared
LDGCOVFLAGS := $(shell if [[ $(coverage) == 1 ]]; then echo \
--coverage \
; else echo ; fi)

$(BUILD_DIR)/$(TARGET): $(OBJS)
	mkdir -p $(dir $@)
	$(CC) -o "$(install_directory)/$(TARGET)" $(OBJS) $(LDFLAGS) $(LDGCOVFLAGS)

$(BUILD_DIR)/%.o:	%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(CDEBUGFLAGS) $(CGCOVFLAGS) -c $< -o $@


.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)
