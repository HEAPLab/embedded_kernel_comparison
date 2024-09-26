##
## Makefile for Miosix embedded OS
##

KPATH := ../miosix-kernel/miosix
CONFPATH := .
MAKEFILE_VERSION := 1.15
include $(KPATH)/Makefile.kcommon

BIN := main

##
## List here your source files (both .s, .c and .cpp)
##
SRC := src/main.cpp

##
## List here additional include directories (in the form -Iinclude_dir)
##
INCLUDE_DIRS :=

##
## List here additional static libraries with relative path
##
LIBS :=

##
## List here subdirectories which contains makefiles
##
SUBDIRS +=

##
## Attach a romfs filesystem image after the kernel
##
ROMFS_DIR := romfs

#BENCHMARKS ?= automotive_qsort consumer_jpeg
#BENCHMARKS ?= telecomm_adpcm
#BENCHMARKS ?= office_stringsearch
BENCHMARKS ?= test_process_blinker
#BENCHMARKS ?= telecomm_crc32

# For running on discovery, every set of benchmark is less than 2MB, size of Flash
#BENCHMARKS ?= \
#    automotive_basicmath \
#    automotive_bitcount \
#    automotive_qsort \
#    automotive_susan \
#    consumer_jpeg \
#    consumer_lame \
#    consumer_mad_large \
#    consumer_mad_small \
#    consumer_tiff2bw
#BENCHMARKS ?= \
#    consumer_tiffdither \
#    consumer_tiffmedian \
#    consumer_typeset_large \
#    consumer_typeset_small \
#    network_dijkstra_large \
#    network_dijkstra_small \
#    network_patricia
#BENCHMARKS ?= \
#    office_ghostscript \
#    office_ispell_large \
#    office_ispell_small \
#    office_rsynth \
#    office_sphinx
#BENCHMARKS ?= \
#    office_stringsearch \
#    security_blowfish \
#    security_pgp \
#    security_rijndael \
#    security_sha \
#    telecomm_adpcm \
#    telecomm_crc32 \
#    telecomm_fft \
#    telecomm_gsm

# For running on blackpill, every set of benchmark is less than 512KB, size of Flash
# BENCHMARKS ?= \
#    automotive_basicmath \
#    automotive_bitcount \
#    consumer_tiff2bw \
#    telecomm_adpcm
# BENCHMARKS ?= \
#    consumer_tiffdither \
#    network_dijkstra_large \
#    network_dijkstra_small
# BENCHMARKS ?= \
#    office_stringsearch \
#    security_blowfish \
#    security_rijndael \
#    security_sha \
#    telecomm_crc32
# BENCHMARKS ?= \
#    telecomm_gsm

#    consumer_tiff2rgba  image size too large

all: $(if $(ROMFS_DIR), image, main)

main: $(OBJ) all-recursive
	$(ECHO) "[LD  ] $(BIN).elf"
	$(Q)$(CXX) $(LFLAGS) -o $(BIN).elf $(OBJ) $(LINK_LIBS)
	$(ECHO) "[CP  ] $(BIN).hex"
	$(Q)$(CP) -O ihex   $(BIN).elf $(BIN).hex
	$(ECHO) "[CP  ] $(BIN).bin"
	$(Q)$(CP) -O binary $(BIN).elf $(BIN).bin
	$(Q)$(SZ) $(BIN).elf

image: prepare-romfs

.PHONY: prepare-romfs
prepare-romfs:
	./prepare_romfs.sh $(BENCHMARKS)

clean: clean-recursive
	$(Q)rm -f $(OBJ) $(OBJ:.o=.d) $(BIN).elf $(BIN).hex $(BIN).bin $(BIN).map

-include $(OBJ:.o=.d)
