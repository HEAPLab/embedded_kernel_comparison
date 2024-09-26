PROCESS_LINUX := $(BIN)_linux

.PHONY: all
all: $(KERNEL) $(PROCESS)

.PHONY: kernel
kernel: $(KERNEL)

.PHONY: process
process: $(PROCESS)

.PHONY: linux
linux: $(PROCESS_LINUX)

.PHONY: $(KERNEL)
$(KERNEL):
	$(MAKE) -f ../makefile_kernel.inc BIN=$(BIN)

.PHONY: $(PROCESS)
$(PROCESS):
	$(MAKE) -f ../makefile_process.inc BIN=$(BIN)

.PHONY: $(PROCESS_LINUX)
$(PROCESS_LINUX):
	$(MAKE) -f ../makefile_linux.inc BIN=$(BIN)

.PHONY: programk
programk: $(KERNEL)
	st-flash --reset write $(KERNEL) 0x8000000

.PHONY: clean
clean:
	$(MAKE) -f ../makefile_kernel.inc BIN=$(BIN) clean
	$(MAKE) -f ../makefile_process.inc BIN=$(BIN) clean
	$(MAKE) -f ../makefile_linux.inc BIN=$(BIN) clean
