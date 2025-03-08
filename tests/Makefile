# this makefile must not be included directly
#
#	@File:      Makefile
#	@Author:    Sam.Nazarov

SHELL   = /bin/bash
TARGET := check_cpathtools

BUILD_DIR := ./build
SRC_DIRS  := 

SRCS := $(shell find $(SRC_DIRS) -name "*.c")
OBJS := $(SRCS:%.c=$(BUILD_DIR)/%.o)

CC := gcc

INCDIRS     := . "$(shell echo `pwd`/../src)"
INCFLAGS    := $(addprefix -I,$(INCDIRS))
CDEBUGFLAGS := -g3 -O0
# https://gcc.gnu.org/onlinedocs/gcc-14.2.0/gcc/Option-Summary.html
CFLAGS      := -Wall -Wextra -Wpedantic -Wshadow -Wformat=2 -Wcast-align \
-Wconversion -Wsign-conversion -Wnull-dereference -fdiagnostics-color=always \
-std=c99 -pedantic $(INCFLAGS)

LIBDIRS := "$(install_directory)"
LDFLAGS := $(addprefix -L,$(LIBDIRS))
LDFLAGS += -lcheck -lcpathtools
# https://github.com/libcheck/check/issues/60
LDFLAGS += $(shell if [[ $(_OS) == linux ]]; then echo \
-lm -lsubunit \
; else echo ; fi)

$(BUILD_DIR)/$(TARGET): $(OBJS)
	mkdir -p $(dir $@)
	$(CC) -o $(TARGET) $(OBJS) $(LDFLAGS)

$(BUILD_DIR)/%.o:	%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(CDEBUGFLAGS) -c $< -o $@


.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)
