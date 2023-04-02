TARGET = messiah
PROGRAM = call-test.bin
OBJS = main.o emulator_function.o instruction.o modrm.o

CC = gcc
ASM = nasm
CFLAGS += -Wall -Wextra

.PHONY: run
run : $(TARGET) $(PROGRAM)
	./$(TARGET) $(PROGRAM)

%.bin : %.asm
	$(ASM) -f bin -o $@ $<

$(TARGET) : $(OBJS)
	$(CC) -o $@ $(OBJS)

%.o : %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(TARGET) $(OBJS) $(PROGRAM)
