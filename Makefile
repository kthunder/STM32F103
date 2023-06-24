# Modify names below
SRC_DIR := src
BLD_DIR := build
ENV_DIR := env
OBJ_DIR := $(BLD_DIR)
TARGET_NAME := main

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

CPU = cortex-m3
ifeq ($(CPU), cortex-m3)
	LD_FILE = STM32F103C6TX_FLASH.ld
	BOARD = STM32F103x6
else
	LD_FILE = STM32F407VETX_FLASH.ld
	BOARD = STM32F407xx
endif

CCFLAGS := -Wall -O0 -g
CCFLAGS += -mcpu=$(CPU) -mthumb -mthumb-interwork
CCFLAGS += -ffunction-sections -fdata-sections -fno-common -fmessage-length=0
CCFLAGS += -D $(BOARD)

CCFLAGS += -I ./src/Core/Inc
CCFLAGS += -I ./src/Drivers/HAL_Driver/Inc
# CCFLAGS += -I ./src/Drivers/FREE_RTOS/Inc
# CCFLAGS += -I ./src/Drivers/FREE_RTOS/portable/GCC_ARM_CM3
CCFLAGS += -I ./src/Drivers/CMSIS/Include
CCFLAGS += -I ./src/Drivers/CMSIS/Device/ST/STM32F1xx/Include

LDFLAGS += -T $(ENV_DIR)/$(LD_FILE)
# LDFLAGS += -nostartfiles -Xlinker -MMD -MP
LDFLAGS += -Wl,--gc-sections,--print-memory-usage,-Map="$(BLD_DIR)/$(TARGET_NAME).map"
LDFLAGS += -mcpu=$(CPU) -mthumb -mthumb-interwork
LDFLAGS += --specs=nosys.specs --specs=nano.specs

ifeq ($(OS),Windows_NT)
   download = $(ENV_DIR)\openocd.cmd $(abspath $(BLD_DIR)/$(TARGET_NAME).elf)
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
	$(OBJCOPY) -Oihex $(BLD_DIR)/$(TARGET_NAME).elf > $(BLD_DIR)/$(TARGET_NAME).hex
	$(OBJCOPY) -Obinary $(BLD_DIR)/$(TARGET_NAME).elf > $(BLD_DIR)/$(TARGET_NAME).bin
	$(OBJDUMP) -D $(BLD_DIR)/$(TARGET_NAME).elf > $(BLD_DIR)/$(TARGET_NAME).dis

$(OBJ) : %.o : % $(HDR)
	mkdir -p $(shell dirname $(BLD_DIR)/$@)
	$(CC) -c $< $(CCFLAGS) -o $(BLD_DIR)/$@

all : $(TARGET_NAME).elf

.PHONY : clean
clean :
	rm -rf $(BLD_DIR)/$(SRC_DIR)

.PHONY : clean_all
clean_all :
	-rm -rf $(BLD_DIR)

.PHONY : download
download :
	compiledb make -j12
	$(call download)
