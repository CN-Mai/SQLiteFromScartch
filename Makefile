# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -g

# Targets
TARGET = SQLiteApp

# Source and object files
SRCS = SQLite.c
OBJS = $(SRCS:.c=.o)

# Default target
all: $(TARGET)

# Rule to build the executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Rule to build object files
%.o: %.c API.h
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -f $(OBJS) $(TARGET)

# Convenience target to clean and rebuild
rebuild: clean all

