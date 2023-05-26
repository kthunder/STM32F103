# 交叉编译工具头,如：arm-none-eabi-
CROSS_COMPILE = arm-none-eabi-
# 编译器别名
AS  = $(CROSS_COMPILE)as  # 把汇编文件生成目标文件
LD  = $(CROSS_COMPILE)ld  # 链接器，为前面生成的目标代码分配地址空间，将多个目标文件链接成一个库或者一个可执行文件
CC  = $(CROSS_COMPILE)gcc # 编译器，对 C 源文件进行编译处理，生成汇编文件
CPP = $(CC) -E
AR  = $(CROSS_COMPILE)ar  # 打包器，用于库操作，可以通过该工具从一个库中删除或则增加目标代码模块
NM  = $(CROSS_COMPILE)nm  # 查看静态库文件中的符号表

STRIP    = $(CROSS_COMPILE)strip   # 以最终生成的可执行文件或者库文件作为输入，然后消除掉其中的源码
OBJCOPY  = $(CROSS_COMPILE)objcopy # 复制一个目标文件的内容到另一个文件中，可用于不同源文件之间的格式转换
OBJDUMP  = $(CROSS_COMPILE)objdump # 查看静态库或则动态库的签名方法


# -Wall ： 允许发出 GCC 提供的所有有用的报警信息
# -O2 : “-On”优化等级
# -g : 在可执行程序中包含标准调试信息
# -I : 指定头文件路径（可多个）
CCFLAGS := -Wall -O2 -g
CCFLAGS += -mcpu=cortex-m3 -mthumb
CCFLAGS += -I ./ASM_StartUp/Core/Inc
CCFLAGS += -I ./ASM_StartUp/Drivers/HAL_Driver/Inc

# LDFLAGS是告诉链接器从哪里寻找库文件，这在本Makefile是链接最后应用程序时的链接选项。
LDFLAGS := -T STM32F103C6TX_FLASH.ld
LDFLAGS += --specs=nosys.specs --specs=nano.specs

#SOURCE FILE DIR
Src_Dir := ./ASM_StartUp/Core/Src
Drv_Dir := ./ASM_StartUp/Drivers/HAL_Driver/Src
Asm_Dir := ./ASM_StartUp/Core/Startup

# foreach表示遍历$(Src_Dir)的所有子目录同时把子目录下的.c文件遍历出来
SRC_C := $(foreach dir, $(Src_Dir), $(wildcard $(dir)/*.c))
SRC_C += $(foreach dir, $(Drv_Dir), $(wildcard $(dir)/*.c))

objs := $(addprefix ,$(patsubst %.c,%.o,$(notdir $(SRC_C))))
dmk := $(addprefix dmk/,$(patsubst %.c,%.d,$(notdir $(SRC_C))))

#objs := $(patsubst %.c, %.o, $(wildcard $(Src_Dir)/*.c))
#objs += $(patsubst %.c, %.o, $(wildcard $(Drv_Dir)/*.c))


#all : startup.elf

test :
	@echo $(dmk)

startup.elf : $(objs) startup.o
	$(CC) $(LDFLAGS) $^ -o $@

# $@ 表示目标
# $^ 表示所有的依赖文件
# $< 表示第一个依赖文件
#$(objs): %.o : %.c
#	$(CC) -c $(CCFLAGS) $< -o ./build/$@
#obj/%.o : $(Src_Dir)/%.c
$(objs): %.o : $(Drv_Dir)/%.c | $(Src_Dir)/%.c
	$(CC) -c $(CCFLAGS) $< -o $@

#startup.o: $(Asm_Dir)/startup.s
#	$(CC) $(CCFLAG) -c $(Asm_Dir)/startup.s

dmk/%.d : $(SRC_C)
	@set -e; rm -f $@; \
	$(CC) -MM $(CCFLAGS) $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,$(D_OBJ)/\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$


include ./dmk

.PHONY : clean
clean : 
	rm *.o *.elf

.PHONY : download
download :
	.\openocd.cmd startup.elf