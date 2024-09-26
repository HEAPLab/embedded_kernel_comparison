BENCH_NAME := telecomm_gsm
SRC        := main.c \
    src/add.c		\
    src/code.c		\
    src/debug.c		\
    src/decode.c		\
    src/long_term.c	\
    src/lpc.c		\
    src/preprocess.c	\
    src/rpe.c		\
    src/gsm_destroy.c	\
    src/gsm_decode.c	\
    src/gsm_encode.c	\
    src/gsm_explode.c	\
    src/gsm_implode.c	\
    src/gsm_create.c	\
    src/gsm_print.c	\
    src/gsm_option.c	\
    src/short_term.c	\
    src/table.c \
    src/toast.c 		\
	src/toast_lin.c	\
	src/toast_ulaw.c	\
	src/toast_alaw.c	\
	src/toast_audio.c

SRC_ABS:=$(patsubst %,../benchmarks/$(BENCH_NAME)/%,$(SRC))

CFLAGS += -I../benchmarks/$(BENCH_NAME)/inc -DSTUPID_COMPILER -DNeedFunctionPrototypes=1 -DSASR

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
