TARGET = liblinked_list.so

OBJECT = linked_list.o

CFLAGS = -Wall -Wextra -fPIC

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJECT)
	$(CC) -shared -o $@ $^

$(OBJECT): linked_list.c linked_list.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECT) $(TARGET)
