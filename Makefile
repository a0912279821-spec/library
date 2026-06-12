CC = gcc
CFLAGS = -Wall -Wextra -std=c11
TARGET = library
SRC = $(wildcard *.c)

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET) *.out
