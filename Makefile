TARGET = address_book

SOURCES = $(wildcard src/*.c)
OBJECTS = $(patsubst src/%.c,%.o,$(SOURCES))

CFLAGS = -Wall -Wextra
CPPFLAGS = -Iinclude

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $^ -o $@

$(OBJECTS): %.o: src/%.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)