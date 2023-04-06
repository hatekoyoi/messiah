TARGET = messiah
PROGRAM = hello.bin
PROGRAM_SELECT = select.bin
OBJS = main.o emulator_function.o instruction.o modrm.o io.o bios.o

CC = gcc
LD = ld
ASM = nasm
CFLAGS += -Wall -Wextra

.PHONY: all run clean
all : $(TARGET) $(PROGRAM)
	./$(TARGET) $(PROGRAM)

run: $(TARGET) $(PROGRAM)
	./$(TARGET) -q $(PROGRAM)

# run: $(TARGET) $(PROGRAM_SELECT)
# 	./$(TARGET) -q $(PROGRAM_SELECT)

$(TARGET) : $(OBJS)
	$(CC) -o $@ $(OBJS)

%.o : %.c
	$(CC) $(CFLAGS) -c $<

%.bin : %.asm
	$(ASM) -f bin -o $@ $<

clean:
	rm -f $(TARGET) $(OBJS) $(PROGRAM)
