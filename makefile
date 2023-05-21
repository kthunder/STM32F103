# 编译器前缀
PREFIX = arm-none-eabi-
# 编译器别名
CC = $(PREFIX)gcc
LD = $(PREFIX)ld

# LDFLAGS
CCFLAG = -mcpu=cortex-m3 -mthumb -I ./ASM_StartUp/Core/Inc -I ./ASM_StartUp/Drivers/HAL_Driver/Inc
LDFLAGS = -T STM32F103C6TX_FLASH.ld --specs=nosys.specs --specs=nano.specs

startup.elf : startup.o main.o
	$(CC) $(LDFLAGS) startup.o main.o -o startup.elf

startup.o : ./ASM_StartUp/Core/Startup/startup.s
	$(CC) $(CCFLAG) -c ./ASM_StartUp/Core/Startup/startup.s

main.o : ./ASM_StartUp/Core/Src/main.c 
	$(CC) $(CCFLAG) -c ./ASM_StartUp/Core/Src/main.c

.PHONY : clean
clean : 
	rm *.o *.elf

.PHONY : download
download :
	..\openocd.cmd startup.elf