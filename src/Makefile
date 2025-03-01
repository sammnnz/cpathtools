TARGET := cpathtools.$$LIB_EXT

BUILD_DIR := ./build
SRC_DIRS  := 

SRCS := $(shell find $(SRC_DIRS) -name "*.c")
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)

CC := gcc

INCDIRS    := "."
INCFLAGS   := $(addprefix -I,$(INCDIRS))
CDEBUGFLAG := -g3 -O0 -fdiagnostics-color=always
CFLAGS 	   := -Wall -Wextra -Wpedantic -Wshadow -Wformat=2 -Wcast-align \
-Wconversion -Wsign-conversion -Wnull-dereference -std=c99 -pedantic \
-fPIC $(INCFLAGS) -DCPATHTOOLSEXPORT

LIBDIRS := 
LDFLAGS := 
LDFLAGS += -shared -DCPATHTOOLSEXPORT

# Inputs (default values)
install_directory := .

$(BUILD_DIR)/$(TARGET): $(OBJS)
	mkdir -p $(dir $@)
	$(CC) -o "$(install_directory)/$(TARGET)" $(OBJS) $(LDFLAGS)

$(BUILD_DIR)/%.c.o:	%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@


.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)
