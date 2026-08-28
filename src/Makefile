TARGET = address_book

LIB_DIR = ../lib
LIBRARY = $(LIB_DIR)/liblinked_list.so

SOURCES = $(wildcard *.c)
OBJECTS = $(SOURCES:.c=.o)

CFLAGS = -Wall -Wextra
CPPFLAGS = -I../include -I../lib

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJECTS) $(LIBRARY)
	$(CC) $(OBJECTS) -L$(LIB_DIR) -llinked_list \
	-Wl,-rpath,'$$ORIGIN/lib' -o ../$(TARGET)

$(OBJECTS): %.o: %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)
