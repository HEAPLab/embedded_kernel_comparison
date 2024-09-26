BENCH_NAME := consumer_jpeg
SRC        := main.c \
src/cjpeg.c \
src/rdppm.c \
src/rdgif.c \
src/rdtarga.c \
src/rdrle.c \
src/rdbmp.c \
src/rdswitch.c \
src/cdjpeg.c \
src/djpeg.c \
src/wrppm.c \
src/wrgif.c \
src/wrtarga.c \
src/wrrle.c \
src/wrbmp.c \
src/rdcolmap.c \
src/jcapimin.c \
src/jcapistd.c \
src/jctrans.c \
src/jcparam.c \
src/jdatadst.c \
src/jcinit.c \
src/jcmaster.c \
src/jcmarker.c \
src/jcmainct.c \
src/jcprepct.c \
src/jccoefct.c \
src/jccolor.c \
src/jcsample.c \
src/jchuff.c \
src/jcphuff.c \
src/jcdctmgr.c \
src/jfdctfst.c \
src/jfdctflt.c \
src/jfdctint.c \
src/jdapimin.c \
src/jdapistd.c \
src/jdtrans.c \
src/jdatasrc.c \
src/jdmaster.c \
src/jdinput.c \
src/jdmarker.c \
src/jdhuff.c \
src/jdphuff.c \
src/jdmainct.c \
src/jdcoefct.c \
src/jdpostct.c \
src/jddctmgr.c \
src/jidctfst.c \
src/jidctflt.c \
src/jidctint.c \
src/jidctred.c \
src/jdsample.c \
src/jdcolor.c \
src/jquant1.c \
src/jquant2.c \
src/jdmerge.c \
src/jcomapi.c \
src/jutils.c \
src/jerror.c \
src/jmemmgr.c \
src/jmemnobs.c

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
