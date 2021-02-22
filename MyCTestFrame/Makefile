CC := gcc
SRC := $(wildcard ./src/*.c)
OBJS := example.o $(SRC:%.c=%.o)
HEADERS := $(wildcard ./include/*.h)

LIBS := 
CFLAGS :=
INCLUDES := -I./include

TARGET := bin/example

$(TARGET) : $(OBJS) $(HEADERS)
	-mkdir bin
	$(CC) $(CFLAGS) $(INCLUDES) $^ -o $@ $(LIBS)

%.o : %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $^ -o $@

.PHONY : run
run : $(TARGET)
	$(TARGET)

.PHONY : clean
clean :
	-rm -rf $(OBJS)	$(TARGET)
