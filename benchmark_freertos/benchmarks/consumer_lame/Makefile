BENCH_NAME := consumer_lame
SRC        := \
    src/brhist.c \
    src/formatBitstream.c \
    src/fft.c \
    src/get_audio.c \
    src/l3bitstream.c \
    src/id3tag.c \
    src/ieeefloat.c \
    src/lame.c \
    src/newmdct.c \
    src/parse.c \
    src/portableio.c \
    src/psymodel.c \
    src/quantize.c \
    src/quantize-pvt.c \
    src/vbrquantize.c \
    src/reservoir.c \
    src/tables.c \
    src/takehiro.c \
    src/timestatus.c \
    src/util.c \
    src/VbrTag.c \
    src/version.c \
    src/gtkanal.c \
    src/gpkplotting.c \
    src/mpglib/common.c \
    src/mpglib/dct64_i386.c \
    src/mpglib/decode_i386.c \
    src/mpglib/layer3.c \
    src/mpglib/tabinit.c \
    src/mpglib/interface.c \
    src/mpglib/mpglib_main.c \
	src/lame_main.c \
	main.c

SRC_ABS:=$(patsubst %,../benchmarks/$(BENCH_NAME)/%,$(SRC))

CFLAGS+=-DHAVEMPGLIB -DLAMEPARSE -DNDEBUG -D__NO_MATH_INLINES -DLAMESNDFILE

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
