BENCH_NAME := security_blowfish
SRC        := main.c src/bf_skey.c src/bf_ecb.c src/bf_enc.c src/bf_cbc.c src/bf_cfb64.c src/bf_ofb64.c src/bf.c

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
