CC = gcc
CFLAGS = -Wall -Wextra -g
DEPS = mytrie.h
OBJDIR = binary
SRCS = mytrie.c test.c
OBJ = $(SRCS:%.c=$(OBJDIR)/%.o)

# Create object directory if it doesn't exist
$(OBJDIR):
	mkdir -p $(OBJDIR)

# Rule for building object files
$(OBJDIR)/%.o: %.c $(DEPS) | $(OBJDIR)
	$(CC) -c -o $@ $< $(CFLAGS)

test: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean
clean:
	rm -rf $(OBJDIR) test

.PHONY: all
all: test