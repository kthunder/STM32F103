# 编译器前缀
PREFIX = arm-none-eabi-
# 编译器别名
CC = $(PREFIX)gcc
LD = $(PREFIX)ld

# LDFLAGS
CCFLAG = -mcpu=cortex-m3 -mthumb
LDFLAGS = -T STM32F103C6TX_FLASH.ld --specs=nosys.specs --specs=nano.specs

startup.elf : startup.o main.o
	$(CC) $(LDFLAGS) startup.o main.o -o startup.elf

startup.o : startup.s
	$(CC) $(CCFLAG) -c startup.s

main.o : main.c stm32f10x.h
	$(CC) $(CCFLAG) -c main.c

.PHONY : clean
clean : 
	rm *.o *.elf

.PHONY : download
download :
	..\openocd.cmd startup.elf