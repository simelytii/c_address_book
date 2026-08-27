TARGET = address_book

SRC_DIR = src
LIB_DIR = lib

SOURCES = $(wildcard $(SRC_DIR)/*.c)
OBJECTS = $(SOURCES:.c=.o)

LIBRARY = $(LIB_DIR)/liblinked_list.so

.PHONY: all clean lib src

all: $(TARGET)

lib:
	$(MAKE) -C $(LIB_DIR)

src:
	$(MAKE) -C $(SRC_DIR)

$(LIBRARY): lib/linked_list.c lib/linked_list.h
	$(MAKE) -C $(LIB_DIR)

$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	$(MAKE) -C $(SRC_DIR)

$(TARGET): $(OBJECTS) $(LIBRARY)
	$(CC) $(OBJECTS) -L$(LIB_DIR) -llinked_list \
	-Wl,-rpath,'$$ORIGIN/lib' -o $@

clean:
	$(MAKE) -C $(LIB_DIR) clean
	$(MAKE) -C $(SRC_DIR) clean
	rm -f $(TARGET)
