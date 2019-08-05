TARGET = kernel7.img
ELFILE = myos.elf 
CC = arm-none-eabi-gcc.exe #cross-compiler
OC = arm-none-eabi-objcopy.exe #object compiler
EM = qemu-system-arm.exe #emulator
CPU = cortex-a7 #target architecture - micro central processing unit
MEM = 1024

SHELL = C:/Windows/system32/cmd.exe

#Flags for compiler (for assembly), 
#-fpic: the compiled code can be placed anywhere in memory - not in an absolute location, 
#-ffreestanding: for bare-metal device standard libraries do not exist, 
#-Wall: warn all
CFLAGS = -mcpu=$(CPU) -fpic -ffreestanding -Wall 

#Flags for emulator
EMFLAGS = -m $(MEM) -M raspi2 -serial stdio -kernel $(OBJS_DIR)/$(ELFILE) 

#Flags for compiling C source file, 
#-g: debugging symbol, 
#-02: optimized level
CSRCFLAGS = -g -O2 -Wall -Wextra

#Flags for linking stage of the build, 
#-nostdlib: don't include any other dll
LFLAGS = -ffreestanding -O2 -nostdlib

SRC_CMN_DIR = ../source/common
SRC_KER_DIR = ../source/kernel
INC_CMN_DIR = ../include/common
INC_KER_DIR = ../include/kernel
OBJS_DIR = objects
EM_DIR = C:\Program Files\qemu
CC_DIR = C:\Program Files (x86)\GNU Tools ARM Embedded\8 2019-q3-update\bin

#Complie all assembly source files in kernel directory, 
#-c: just compile following C source or assembly files, do not do linking, 
#-o: output
$(OBJS_DIR)/%.o : $(SRC_KER_DIR)/%.s
	@echo Compiling Assembler Source File $<
	@$(CC_DIR)/$(CC) $(CFLAGS) -c $< -o $@

#Compile all C source files in common directory, 
#-I: include header files, 
#$<: leftmost current dependency
$(OBJS_DIR)/%.o : $(SRC_CMN_DIR)/%.c $(INC_CMN_DIR)/%.h
	@echo Compiling C source file $< in common directory
	@$(CC_DIR)/$(CC) $(CFLAGS) -I$(INC_CMN_DIR) -I$(INC_KER_DIR) -c $< -o $@ $(CSRCFLAGS)

#Compile all C source files in kernel directory, 
#-I: include header files, 
#$<: leftmost current dependency. 
$(OBJS_DIR)/%.o : $(SRC_KER_DIR)/%.c $(INC_KER_DIR)/%.h
	@echo Compiling C source file $< in common directory
	@$(CC_DIR)/$(CC) $(CFLAGS) -I$(INC_CMN_DIR) -I$(INC_KER_DIR) -c $< -o $@ $(CSRCFLAGS)

#Link all object files
$(OBJS_DIR)/$(ELFILE) : $(OBJS_DIR)/boot.o $(OBJS_DIR)/stdio.o $(OBJS_DIR)/mystdlib.o $(OBJS_DIR)/kernel.o $(OBJS_DIR)/uart.o $(OBJS_DIR)/gpio.o $(OBJS_DIR)/master.o 
	@echo Linking Objects Files: $^
	@$(CC_DIR)/$(CC) -T linker.ld -o $(OBJS_DIR)/$(ELFILE) $(LFLAGS) $^
	@echo Extensible Linkable Format File: $@ created

#Convert elf file to img file
$(TARGET) : $(OBJS_DIR)/$(ELFILE)
	@$(CC_DIR)/$(OC) $(OBJS_DIR)/$(ELFILE) -O binary $(OBJS_DIR)/$(TARGET)
	@echo Kernel Image File: $(TARGET) created

#Target to call from the command line
all: $(TARGET)

clean:
	@echo Removing Object Files $(wildcard $(OBJS_DIR)/*.o)
	@del  $(OBJS_DIR)\*.o 
	@echo Removing $(ELFILE)
	@del  $(OBJS_DIR)\*.elf 
	@echo Removing $(TARGET)
	@del  $(OBJS_DIR)\*.img

.PHONY: clean run all

run: $(OBJS_DIR)/$(ELFILE)
	$(EM_DIR)/$(EM) $(EMFLAGS)

