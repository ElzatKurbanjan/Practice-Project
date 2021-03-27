TARGET := ls
SRC := $(wildcard ./*.c)
OBJS := $(SRC:%.c=%.o)

INCLUDES := -I$(TOP_DIR)/common_headers

$(TARGET) : $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@; \
	mv $(TARGET) $(TOP_DIR)/$(OUTPUT_DIR)

%.o : %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

%.d : %.c
	@set -e; rm -f $@;\
	$(CC) -MM $(CFLAGS) $(INCLUDES) $< > $@.$$$$; \
	sed 's, \($*\).o[ :]*,\1.o $@ :,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$

-include $(SRC:%.c=%.d)

.PHONY : clean
clean:
	-rm -rf *.o *.d