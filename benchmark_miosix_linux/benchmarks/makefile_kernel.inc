##
## Makefile for Miosix embedded OS
##

KPATH := ../../miosix-kernel/miosix
CONFPATH := ../_common
OBJ_DIR := kernel_obj
MAKEFILE_VERSION := 1.15
include $(KPATH)/Makefile.kcommon

BIN ?= main

-include Makefile.kernel

##
## List here subdirectories which contains makefiles
##
SUBDIRS := $(KPATH)

CFLAGS += $(BENCHMARK_CFLAGS)
CXXFLAGS += $(BENCHMARK_CXXFLAGS)

all: $(if $(ROMFS_DIR), image, main)

main: $(OBJ) all-recursive
	$(ECHO) "[LD  ] $(BIN).elf"
	$(Q)$(CXX) $(LFLAGS) -Wl,-Map,$(BIN).map -o $(BIN).elf $(OBJ) $(LINK_LIBS)
	$(ECHO) "[CP  ] $(BIN).hex"
	$(Q)$(CP) -O ihex   $(BIN).elf $(BIN).hex
	$(ECHO) "[CP  ] $(BIN).bin"
	$(Q)$(CP) -O binary $(BIN).elf $(BIN).bin
	$(Q)$(SZ) $(BIN).elf

clean: clean-recursive
	$(Q)rm -f $(OBJ) $(OBJ:.o=.d) $(BIN).elf $(BIN).hex $(BIN).bin $(BIN).map

-include $(OBJ:.o=.d)
