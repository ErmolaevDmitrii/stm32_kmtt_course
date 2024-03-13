# Please set path to your project directory
# and your arm-none-eabi-gcc toolchain
PRJ = /home/ermolaev/Documents/stm32_kmtt_course/uart_task
CCPATH = /opt/gcc-arm-none-eabi/bin

########################################################################
CC=$(CCPATH)/arm-none-eabi-gcc
LD=$(CCPATH)/arm-none-eabi-gcc
CP=$(CCPATH)/arm-none-eabi-objcopy

########################################################################
LDSCRIPT = -T$(PRJ)/STM32F746NGHx_FLASH.ld

########################################################################
INC += -I$(PRJ)/Inc
INC += -I/home/ermolaev/STM32CubeF7/Drivers/CMSIS/Device/ST/STM32F7xx/Include
INC += -I/home/ermolaev/STM32CubeF7/Drivers/CMSIS/Include

SRC += $(PRJ)/Src/main.c
SRC += $(PRJ)/Src/system_stm32f7xx.c

ASM += $(PRJ)/startup_stm32f746xx.s

#######################################################################
OBJ=$(SRC:%.c=%.o)
OBJ+=$(ASM:%.s=%.o)

#######################################################################
CFLAGS += -mcpu=cortex-m7
CFLAGS += -mlittle-endian
CFLAGS += -mthumb
CFLAGS += -g
CFLAGS += $(INC)

LDFLAGS += -mcpu=cortex-m7
LDFLAGS += -mlittle-endian
LDFLAGS += -mthumb
LDFLAGS += $(LDSCRIPT)
LDFLAGS += -Wl,--gc-section

CDEFS = -DSTM32F746xx

######################################################################

all: main.elf
	@echo "\n"
	@echo "END"

main.elf: $(OBJ)
	@echo "\n"
	@echo "LINK"
	@echo "********************************************************"
	$(LD) $(LDFLAGS) $(OBJ) -o main.elf
	@echo "********************************************************"

%.o: %.c
	@echo "\n"
	@echo "COMPILE C"
	@echo "********************************************************"
	$(CC) $(CFLAGS) $(CDEFS) -c $< -o $@
	@echo "********************************************************"

%.o: %.s
	@echo "\n"
	@echo "COMPILE S"
	@echo "********************************************************"
	$(CC) $(CFLAGS) -c $< -o $@
	@echo "********************************************************"

clean:
	rm -f $(OBJ) main.elf main.hex

flash:
	$(CP) -O binary main.elf main.bin
	st-flash --reset write main.bin 0x8000000
