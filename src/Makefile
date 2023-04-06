TARGET = messiah
PROGRAM = select.bin
OBJS = main.o emulator_function.o instruction.o modrm.o io.o
TEST_OBJS = select.o

CC = gcc
LD = ld
ASM = nasm
CFLAGS += -Wall -Wextra

.PHONY: debug run
debug : $(TARGET) $(PROGRAM)
	./$(TARGET) $(PROGRAM)

run : $(TARGET) $(PROGRAM)
	./$(TARGET) -q $(PROGRAM)

select.o : select.asm
	$(ASM) -f elf $<

%.bin : %.asm
	$(ASM) -f bin -o $@ $<

%.o : %.c
	$(CC) $(CFLAGS) -c $<

$(TARGET) : $(OBJS)
	$(CC) -o $@ $(OBJS)

clean:
	rm -f $(TARGET) $(OBJS) $(PROGRAM) $(TEST_OBJS)
