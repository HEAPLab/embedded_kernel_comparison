BIN := test_kernel_blinker
KERNEL := $(BIN).bin

.PHONY: all
all: $(KERNEL) $(PROCESS)

.PHONY: kernel
kernel: $(KERNEL)

.PHONY: $(KERNEL)
$(KERNEL):
	$(MAKE) -f ../makefile_kernel.inc BIN=$(BIN)

.PHONY: programk
programk: $(KERNEL)
	st-flash --reset write $(KERNEL) 0x8000000

.PHONY: clean
clean:
	$(MAKE) -f ../makefile_kernel.inc BIN=$(BIN) clean

