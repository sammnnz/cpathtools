TARGET := cpathtools.$$LIB_EXT

BUILD_DIR := ./build
SRC_DIRS  := 

SRCS := $(shell find $(SRC_DIRS) -name "*.c")
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)

CC := gcc

INCDIRS     := .
INCFLAGS    := $(addprefix -I,$(INCDIRS))
CDEBUGFLAGS := $(shell if [ $(debug) == 1 ]; then echo -g3 -O0; else echo ; fi)
# https://gcc.gnu.org/onlinedocs/gcc-14.2.0/gcc/Option-Summary.html
CFLAGS 	    := -Wall -Wextra -Wpedantic -Wshadow -Wformat=2 -Wcast-align \
-Wconversion -Wsign-conversion -Wnull-dereference -fdiagnostics-color=always \
-fvisibility=hidden -std=c99 -pedantic -fPIC -O2 $(INCFLAGS) -DBUILDING_DLL

LIBDIRS := 
LDFLAGS := 
LDFLAGS += -shared

# Inputs (default values)
debug = 0
install_directory := .

$(BUILD_DIR)/$(TARGET): $(OBJS)
	mkdir -p $(dir $@)
	$(CC) -o "$(install_directory)/$(TARGET)" $(OBJS) $(LDFLAGS)

$(BUILD_DIR)/%.c.o:	%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(CDEBUGFLAGS) -c $< -o $@


.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)
