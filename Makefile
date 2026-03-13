CC = gcc
CFLAGS = -Wall -Wextra -O2 -lm
TARGET = color_editor
SRC = color_editor.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(SRC) -o $(TARGET) $(CFLAGS)

clean:
	rm -f $(TARGET)

.PHONY: all clean