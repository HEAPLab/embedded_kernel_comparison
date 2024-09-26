-include Makefile.process

BIN ?= main

OBJ_DIR := linux_obj

OBJ := $(patsubst %, $(OBJ_DIR)/%, $(addsuffix .o, $(basename $(SRC))))
BIN_ELF := $(BIN)_linux

AS  := arm-linux-as
CC  := arm-linux-gcc
CXX := arm-linux-g++
SZ  := arm-linux-size

CFLAGS   := $(BENCHMARK_CFLAGS) $(BENCHMARK_CFLAGS_LINUX) -ffunction-sections -O2 $(INCLUDE_DIRS) -g -DMIBENCH_PROCESS_MODE -DMIBENCH_LINUX
CXXFLAGS := $(BENCHMARK_CXXFLAGS) -ffunction-sections -O2 $(INCLUDE_DIRS) -g -DMIBENCH_PROCESS_MODE -DMIBENCH_LINUX
LFLAGS   := -Wl,--gc-sections
DFLAGS    := -MMD -MP

LINK_LIBS := -lm

.PHONY: all
all: $(BIN_ELF)

$(BIN_ELF): $(OBJ)
	$(CXX) $(LFLAGS) -o $(BIN_ELF) $(OBJ) $(LINK_LIBS)

.PHONY: clean
clean:
	rm -rf $(OBJ_DIR)
	rm -f $(BIN_ELF) $(BIN_MAP)
	rm -f *.gdb

$(OBJ_DIR)/%.o: %.s
	$(CC) $(AFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: %.S
	$(CC) $(AFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: %.c
	$(CC) $(DFLAGS) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o : %.cpp
	$(CXX) $(DFLAGS) $(CXXFLAGS) -c $< -o $@

$(OBJ): | $(OBJ_DIR)

$(OBJ_DIR):
	mkdir -p $(sort $(dir $(OBJ)))

#pull in dependency info for existing .o files
-include $(OBJ:.o=.d)
