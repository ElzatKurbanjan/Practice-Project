TOP_DIR = $(shell pwd)
SRC_DIR := src
SRC_DIRS := $(foreach dir, $(SRC_DIR), $(wildcard $(SRC_DIR)/*))
OUTPUT_DIR := bin
CC := gcc
CFLAGS := -Wall -Werror

export TOP_DIR
export CC
export CFLAGS
export OUTPUT_DIR

.PHONY : all $(SRC_DIRS) clean
all : $(SRC_DIRS)

$(SRC_DIRS) : 
	$(MAKE) -C $@

clean:
	$(foreach dir, $(SRC_DIRS), $(shell cd $(dir) && make clean))
	-rm -rf $(OUTPUT_DIR)/*