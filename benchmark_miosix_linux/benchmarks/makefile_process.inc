##
## Makefile for writing PROCESSES for the Miosix embedded OS
##

-include Makefile.process

## KPATH and CONFPATH can be specified here or forwarded by the parent makefile
KPATH := ../../miosix-kernel/miosix
LIBSYS  := $(KPATH)/libsyscalls
CONFPATH := ../_common
OBJ_DIR := process_obj
TOOLS_DIR := $(KPATH)/_tools
MAKEFILE_VERSION := 1.15
include $(KPATH)/libsyscalls/Makefile.pcommon

BIN ?= main
PROCESS_RAMSIZE ?= $$((2048*1024))
PROCESS_STACKSIZE ?= 4096

# configuration options:
# -DMIBENCH_NO_SMALL -DMIBENCH_NO_LARGE -DMIBENCH_NO_PROFILING

CFLAGS   += $(BENCHMARK_CFLAGS) -DMIBENCH_PROCESS_MODE
CXXFLAGS += $(BENCHMARK_CXXFLAGS) -DMIBENCH_PROCESS_MODE

.PHONY: all
all: $(OBJ) $(OBJ_DIR)/libsyscalls.a
	$(ECHO) "[LD  ] $(BIN)"
	$(Q)$(CXX)    $(LFLAGS) -o $(BIN) $(OBJ) $(LINK_LIBS)
	$(Q)$(SZ)     $(BIN)
	$(Q)$(STRIP)  $(BIN)
	$(Q)$(POSTLD) $(BIN) --ramsize=$(PROCESS_RAMSIZE) --stacksize=$(PROCESS_STACKSIZE) --strip-sectheader

$(OBJ_DIR)/libsyscalls.a:
	$(Q)$(MAKE) -C $(LIBSYS)                                               \
	KPATH=$(shell perl $(TOOLS_DIR)/relpath.pl $(LIBSYS) $(KPATH))         \
	CONFPATH=$(shell perl $(TOOLS_DIR)/relpath.pl $(LIBSYS) $(CONFPATH))   \
	OBJ_DIR=$(shell perl $(TOOLS_DIR)/relpath.pl $(LIBSYS) $(OBJ_DIR))     \
	|| exit 1;

.PHONY: clean
clean:
	$(Q)rm -f $(OBJ) $(OBJ:.o=.d) $(BIN) $(notdir $(BIN)).map

-include $(OBJ:.o=.d)
