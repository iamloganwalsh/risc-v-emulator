CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -std=c2x -g -MMD -MP

TARGET = vm

SRCS = vm.c virtual_routines.c register_dump.c instructions.c initialisation.c heapbanks.c decoding.c
OBJS = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET) $(OBJS:.o=.d)

-include $(OBJS:.o=.d)