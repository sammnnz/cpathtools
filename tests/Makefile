TARGET := check_cpathtools

BUILD_DIR := ./build
SRC_DIRS  := 

SRCS := $(shell find $(SRC_DIRS) -name "*.c")
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)

CC := gcc

INCDIRS     := . "$(shell echo `pwd`/../src)"
INCFLAGS    := $(addprefix -I,$(INCDIRS))
# https://gcc.gnu.org/onlinedocs/gcc-14.2.0/gcc/Option-Summary.html
CFLAGS      := -Wall -Wextra -Wpedantic -Wshadow -Wformat=2 -Wcast-align \
-Wconversion -Wsign-conversion -Wnull-dereference -fdiagnostics-color=always \
-std=c99 -pedantic -O2 $(INCFLAGS)

LIBDIRS  = "$$LIBGCC_DIRECTORY" "$(install_directory)"
LDFLAGS := $(addprefix -L,$(LIBDIRS))
LDFLAGS += -lcheck -lcpathtools

# Inputs (default values)
CDEBUGFLAGS := -g3 -O0
install_directory = .

$(BUILD_DIR)/$(TARGET): $(OBJS)
	mkdir -p $(dir $@)
	$(CC) -o $(TARGET) $(OBJS) $(LDFLAGS)

$(BUILD_DIR)/%.c.o:	%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(CDEBUGFLAGS) -c $< -o $@


.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)
