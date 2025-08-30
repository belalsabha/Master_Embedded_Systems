#@copyright : $(PRINT-A-NAME)

CC=arm-none-eabi

CFLAGS=-g  -mcpu=arm926ej-s

INCS= -I .

LIBS=   

SRC=$(wildcard *.c)

OBJ=// uart.c app.c startup.o          (SRC.c*.o)

AS=$(wildcard *.s)

ASO=$(AS .s*.o)

PROJECT_NAME=PRINT-A-NAME




all: $(PRINT-A-NAME).bin
	@echo "build is done"

startup.o   /*target*/ : startup.s // dependencies 
	$(CC)-as.exe $(CFLAGS) $<// dependencies -o  $@//target

%.o: %.c 
	$(CC)-gcc.exe -c   $(CFLAGS) $(INCS)  $< -o  $@


	
$(PRINT-A-NAME).elf: $(OBJ) $(ASO)
 $(CC)-ld.exe -T linker.ld $(LIBS) $(OBJ) $(ASO)

$(PRINT-A-NAME).bin: $(PRINT-A-NAME).elf 
 $(CC)-objcopy.exe -o binary $<  $@
clean all:
	rm *.o *.elf *.bin 

clean all:
	rm  *.elf *.bin 
