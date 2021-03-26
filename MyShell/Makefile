TOP_DIR = $(shell pwd)
SRC_DIR := src
SRC_DIRS := $(foreach dir, $(SRC_DIR), $(wildcard $(SRC_DIR)/*))
CC := gcc
CFLAGS := -Wall -Werror

MAKE += -Icommon_headers

export TOP_DIR
export CC
export CFLAGS

.PHONY : all $(SRC_DIRS) clean
all : $(SRC_DIRS)

$(SRC_DIRS) : 
	$(MAKE) -C $@

clean:
	rm ./src/ls/ls.o ./src/ls/ls