SOURCES = $(wildcard *.c)
OBJECTS = $(SOURCES:.c=.o)

CFLAGS = -Wall -Wextra
CPPFLAGS = -I../include -I../lib

.PHONY: all clean

all: $(OBJECTS)

$(OBJECTS): %.o: %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS)
