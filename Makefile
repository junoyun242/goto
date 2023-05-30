CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic
TARGET = goto
SRCS = main.c cmd.c file.c

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS)

.PHONY: clean
clean:
	rm -f $(TARGET)