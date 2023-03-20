TARGET = messiah
PROGRAM = helloworld.bin
OBJS = main.o

CC = gcc
CFLAGS += -Wall -Wextra

.PHONY: run
run : $(TARGET) $(PROGRAM)
	./$(TARGET) $(PROGRAM)

%.bin : %.asm
	nasm -f bin -o $@ $<

$(TARGET) : $(OBJS)
	$(CC) -o $@ $(OBJS)

%.o : %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(TARGET) $(OBJS) $(PROGRAM)
