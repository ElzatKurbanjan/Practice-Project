CC := gcc
SRC := $(wildcard ./src/*.c) example.c
OBJS := $(SRC:%.c=%.o) example.o

LIBS := 
CFLAGS :=
INCLUDES := -I./include

TARGET := bin/example

$(TARGET) : $(OBJS)
	-mkdir bin; \
	$(CC) $(CFLAGS) $(INCLUDES) $^ -o $@ $(LIBS)

%.o : %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

%.d : %.c
	@set -e; rm -f $@;\
	$(CC) -MM $(CFLAGS) $(INCLUDES) $< > $@.$$$$; \
	sed 's, \($*\).o[ :]*,\1.o $@ :,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$

-include $(SRC:%.c=%.d)

.PHONY : run
run : $(TARGET)
	$(TARGET)

.PHONY : clean
clean :
	-rm -rf $(OBJS)	$(TARGET) *.d src/*.d
