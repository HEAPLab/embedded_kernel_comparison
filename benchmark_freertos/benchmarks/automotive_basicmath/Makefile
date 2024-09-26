BENCH_NAME := automotive_basicmath

SRC := \
main.c \
src/basicmath_large.c \
src/basicmath_small.c \
src/cubic.c \
src/isqrt.c \
src/rad2deg.c

BENCH_DIR:=../benchmarks/$(BENCH_NAME)
SRC_ABS:=$(patsubst %,$(BENCH_DIR)/%,$(SRC))

.PHONY: all
all: main.bin

.PHONY: main.bin
main.bin:
	$(MAKE) -C ../../lib SRC_BENCH="$(SRC_ABS)" clean
	$(MAKE) -C ../../lib SRC_BENCH="$(SRC_ABS)" \
	    && cp ../../lib/build/freertos_stm32f469disco_skel.bin main.bin

.PHONY: program
program: main.bin
	st-flash --connect-under-reset --reset write main.bin 0x8000000

.PHONY: clean
clean:
	$(MAKE) -C ../../lib SRC_BENCH="$(SRC_ABS)" clean
	rm -f main.bin
