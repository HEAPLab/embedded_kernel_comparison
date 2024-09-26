BENCH_NAME := telecomm_fft
SRC        := main.c src/fftmisc.c src/fourierf.c src/fft_main.c

SRC_ABS:=$(patsubst %,../benchmarks/$(BENCH_NAME)/%,$(SRC))

CFLAGS+=

.PHONY: all
all: main.bin

.PHONY: main.bin
main.bin:
	$(MAKE) -C ../../lib SRC_BENCH="$(SRC_ABS)" CFLAGS_BENCH="$(CFLAGS)" clean
	$(MAKE) -C ../../lib SRC_BENCH="$(SRC_ABS)" CFLAGS_BENCH="$(CFLAGS)" && cp ../../lib/build/freertos_stm32f469disco_skel.bin main.bin

.PHONY: program
program: main.bin
	st-flash --connect-under-reset --reset write main.bin 0x8000000

.PHONY: clean
clean:
	$(MAKE) -C ../../lib SRC_BENCH="$(SRC_ABS)" CFLAGS_BENCH="$(CFLAGS)" clean
	rm -f main.bin
