SRC_DIR = src
LIB_DIR = lib

.PHONY: all clean lib src

all: lib src

lib:
	$(MAKE) -C $(LIB_DIR)

src:
	$(MAKE) -C $(SRC_DIR)

clean:
	$(MAKE) -C $(LIB_DIR) clean
	$(MAKE) -C $(SRC_DIR) clean