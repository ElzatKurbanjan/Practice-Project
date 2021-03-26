TARGET := ls
SRC := $(wildcard ./*.c)
OBJS := $(SRC:%.c=%.o)

INCLUDES := -I$(TOP_DIR)/commen_headers
HEADERS := $(wildcard $(TOP_DIR)/common_headers/*.h)

$(TARGET) : $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

%.o : %.c
	$(CC) $(CFLAGS) -c $^ -o $@