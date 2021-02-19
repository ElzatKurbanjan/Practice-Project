CC := gcc
SRC := $(wildcard ./src/*.c)
OBJS := example.o $(SRC:%.c=%.o)

LIBS := 
CFLAGS :=
INCLUDES := -I./include

TARGET := ./bin/example

$(TARGET) : $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

%.o : %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $^ -o $@

.PHONY : run
run : $(TARGET)
	$(TARGET)

.PHONY : clean
clean :
	-rm $(OBJS)	$(TARGET)
