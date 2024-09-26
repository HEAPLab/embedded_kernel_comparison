BENCH_NAME := automotive_bitcount
SRC        := main.c src/bitcnt_1.c src/bitcnt_2.c src/bitcnt_3.c src/bitcnt_4.c src/bitcnts.c src/bitfiles.c src/bitstrng.c src/bstr_i.c

SRC_ABS:=$(patsubst %,../benchmarks/$(BENCH_NAME)/%,$(SRC))

.PHONY: all
all: main.bin

.PHONY: main.bin
main.bin:
	$(MAKE) -C ../../lib SRC_BENCH="$(SRC_ABS)" clean
	$(MAKE) -C ../../lib SRC_BENCH="$(SRC_ABS)" && cp ../../lib/build/freertos_stm32f469disco_skel.bin main.bin

.PHONY: program
program: main.bin
	st-flash --connect-under-reset --reset write main.bin 0x8000000

.PHONY: clean
clean:
	$(MAKE) -C ../../lib SRC_BENCH="$(SRC_ABS)" clean
	rm -f main.bin
