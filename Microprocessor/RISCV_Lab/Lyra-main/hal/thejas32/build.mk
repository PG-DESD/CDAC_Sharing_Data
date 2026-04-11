######################################
# target
######################################
ifndef TARGET
TARGET = app
endif

######################################
# building variables
######################################

# optimization
ifndef OPT
OPT = -Og
endif

#######################################
# paths
#######################################
# Build path
BUILD_DIR = build

######################################
# source
######################################
# C sources
C_SOURCES += \
$(wildcard $(VEGA_SDK_PATH)/drivers/*.c) \
$(wildcard $(VEGA_SDK_PATH)/libs/*.c)

# ASM sources
ASM_SOURCES +=  \
$(VEGA_SDK_PATH)/startup_thejas32.s 

#######################################
# binaries
#######################################
ifndef CROSS_COMPILE
CROSS_COMPILE = riscv-none-elf-
endif
# The gcc compiler bin path can be either defined in make command via CC_PATH variable (> make CC_PATH=xxx)
# or it can be added to the PATH environment variable.
ifdef CC_PATH
CC = $(CC_PATH)/$(CROSS_COMPILE)gcc
AS = $(CC_PATH)/$(CROSS_COMPILE)gcc -x assembler-with-cpp
CP = $(CC_PATH)/$(CROSS_COMPILE)objcopy
SZ = $(CC_PATH)/$(CROSS_COMPILE)size
else
CC = $(CROSS_COMPILE)gcc
AS = $(CROSS_COMPILE)gcc -x assembler-with-cpp
CP = $(CROSS_COMPILE)objcopy
SZ = $(CROSS_COMPILE)size
endif
HEX = $(CP) -O ihex
BIN = $(CP) -O binary -S
 
#######################################
# CFLAGS
#######################################
# Memory model
CODEMODEL = -mcmodel=medany

#ISA Arch
ARCH = -march=rv32im_zicsr_zifencei

# ABI
ABI = -mabi=ilp32

# mcu
MCU = $(CODEMODEL) $(ARCH) $(ABI)

# macros for gcc
# AS defines
AS_DEFS += 

# C defines
C_DEFS +=  

# AS includes
AS_INCLUDES += 

# C includes
C_INCLUDES += \
-I/usr/local/include

# Compile gcc flags
ASFLAGS = $(MCU) $(AS_DEFS) $(AS_INCLUDES) $(OPT) -Wall -fdata-sections -ffunction-sections

CFLAGS = $(MCU) $(C_DEFS) $(C_INCLUDES) $(OPT) -Wall -fdata-sections -ffunction-sections

ifndef BOOTSEL
BOOTSEL = 1
endif

FLASHER = xmodem

# Generate dependency information
CFLAGS += -MMD -MP -MF"$(@:%.o=%.d)"


#######################################
# LDFLAGS
#######################################
# link script
ifeq ($(BOOTSEL), 1)
LDSCRIPT = $(VEGA_SDK_PATH)/thejas32flash.ld
else
LDSCRIPT = $(VEGA_SDK_PATH)/thejas32ram.ld
endif

# libraries
LIBS += -lc -lm -lnosys 
LIBDIR += 
LDFLAGS = $(MCU) -specs=nano.specs -nostartfiles -T$(LDSCRIPT) $(LIBDIR) $(LIBS) -Wl,-Map=$(BUILD_DIR)/$(TARGET).map,--cref -Wl,--gc-sections

# default action: build all
all: $(BUILD_DIR)/$(TARGET).elf $(BUILD_DIR)/$(TARGET).hex $(BUILD_DIR)/$(TARGET).bin


#######################################
# build the application
#######################################
# list of objects
OBJECTS = $(addprefix $(BUILD_DIR)/,$(notdir $(C_SOURCES:.c=.o)))
vpath %.c $(sort $(dir $(C_SOURCES)))
# list of ASM program objects
OBJECTS += $(addprefix $(BUILD_DIR)/,$(notdir $(ASM_SOURCES:.s=.o)))
vpath %.s $(sort $(dir $(ASM_SOURCES)))

$(BUILD_DIR)/%.o: %.c Makefile | $(BUILD_DIR) 
	@-$(CC) -c $(CFLAGS) -Wa,-a,-ad,-alms=$(BUILD_DIR)/$(notdir $(<:.c=.lst)) $< -o $@

$(BUILD_DIR)/%.o: %.s Makefile | $(BUILD_DIR)
	@-$(AS) -c $(CFLAGS) $< -o $@

$(BUILD_DIR)/$(TARGET).elf: $(OBJECTS) Makefile
	@-$(CC) $(OBJECTS) $(LDFLAGS) -o $@
	@-$(SZ) $@

$(BUILD_DIR)/%.hex: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	@-$(HEX) $< $@
	
$(BUILD_DIR)/%.bin: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	@-$(BIN) $< $@	
	
$(BUILD_DIR):
	@-mkdir $@		

#######################################
# Phony targets
#######################################
.PHONY:	clean flash

#######################################
# clean up
#######################################
clean:
	@echo Cleaning up build artifacts...
	@-rm -rf $(BUILD_DIR)

#######################################
# clean up
#######################################
flash:
	$(VEGA_SDK_PATH)/$(FLASHER) /dev/ttyUSB0 $(BUILD_DIR)/$(TARGET).bin

#######################################
# dependencies
#######################################
-include $(wildcard $(BUILD_DIR)/*.d)

# *** EOF ***