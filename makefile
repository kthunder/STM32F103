# Modify names below
SRC_DIR := ASM_StartUp
BLD_DIR := build
ENV_DIR := env
OBJ_DIR := $(BLD_DIR)
TARGET_NAME := startup

CROSS_COMPILE = arm-none-eabi-
AS  = $(CROSS_COMPILE)as
LD  = $(CROSS_COMPILE)ld
CC  = $(CROSS_COMPILE)gcc
CPP = $(CC) -E
AR  = $(CROSS_COMPILE)ar
NM  = $(CROSS_COMPILE)nm

STRIP    = $(CROSS_COMPILE)strip
OBJCOPY  = $(CROSS_COMPILE)objcopy
OBJDUMP  = $(CROSS_COMPILE)objdump

CCFLAGS := -Wall -O2 -g
CCFLAGS += -mcpu=cortex-m3 -mthumb @path.include

LDFLAGS := -T $(ENV_DIR)/STM32F103C6TX_FLASH.ld
LDFLAGS += --specs=nosys.specs --specs=nano.specs

ifeq ($(OS),Windows_NT)
   download = $(ENV_DIR)\openocd.cmd $(abspath $(BLD_DIR)\$(TARGET_NAME).elf)
else
   download = echo "Not implement"
endif

vpath %.c $(SRC_DIR)
vpath %.s $(SRC_DIR)
vpath %.S $(SRC_DIR)

SRC := $(shell find $(SRC_DIR) -type f -name "*" | grep -E -i ".\.(c|s)")
HDR := $(shell find $(SRC_DIR) -type f -name "*" | grep -E -i ".\.(h)")
OBJ := $(patsubst $(SRC_DIR)/%, $(SRC_DIR)/%.o, $(SRC))

$(TARGET_NAME).elf : $(OBJ)
	$(CC) $(LDFLAGS) $(patsubst %, $(BLD_DIR)/%, $^) -o $(BLD_DIR)/$@

$(OBJ) : %.o : % $(HDR)
	mkdir -p $(shell dirname $(BLD_DIR)/$@)
	$(CC) -c $< $(CCFLAGS) -o $(BLD_DIR)/$@

.PHONY : clean
clean :
	rm -rf $(BLD_DIR)/$(SRC_DIR)

.PHONY : clean_all
clean_all :
	-rm -rf $(BLD_DIR)

.PHONY : download
download :
	$(call download)
