BENCHMARKS := \
    automotive_basicmath \
    automotive_bitcount \
    automotive_qsort \
    automotive_susan \
    consumer_jpeg \
    consumer_lame \
    consumer_mad_large \
    consumer_mad_small \
    consumer_tiff2bw \
    consumer_tiff2rgba \
    consumer_tiffdither \
    consumer_tiffmedian \
    consumer_typeset_large \
    consumer_typeset_small \
    network_dijkstra_large \
    network_dijkstra_small \
    network_patricia \
    office_ghostscript \
    office_ispell_large \
    office_ispell_small \
    office_rsynth \
    office_sphinx \
    office_stringsearch \
    security_blowfish \
    security_pgp \
    security_rijndael \
    security_sha \
    telecomm_adpcm \
    telecomm_crc32 \
    telecomm_fft \
    telecomm_gsm

BENCHMARKS_KERNEL := $(patsubst %,%_kernel,$(BENCHMARKS))
BENCHMARKS_LINUX := $(patsubst %,%_linux,$(BENCHMARKS))
BENCHMARKS_CLEAN := $(patsubst %,%_clean,$(BENCHMARKS))

.PHONY: all
all: all_kernel all_process all_linux

.PHONY: all_kernel
all_kernel: $(BENCHMARKS_KERNEL)

.PHONY: all_process
all_process:
	for b in $(BENCHMARKS); do \
	  $(MAKE) -C process-launcher BENCHMARKS=$$b clean; \
	  $(MAKE) -C process-launcher BENCHMARKS=$$b; \
	  cp process-launcher/image.bin $${b}_process.bin; \
	done

.PHONY: all_linux
all_linux: $(BENCHMARKS_LINUX)

.PHONY: $(BENCHMARKS_KERNEL)
$(BENCHMARKS_KERNEL):
	$(MAKE) -C $(patsubst %_kernel,benchmarks/%,$@) kernel
	cp benchmarks/$(patsubst %_kernel,%,$@)/$(patsubst %_kernel,%,$@).bin $@.bin

.PHONY: $(BENCHMARKS_LINUX)
$(BENCHMARKS_LINUX):
	$(MAKE) -C $(patsubst %_linux,benchmarks/%,$@) linux
	cp benchmarks/$(patsubst %_linux,%,$@)/$@ .

.PHONY: clean
clean: all_clean

.PHONY: all_clean
all_clean: $(BENCHMARKS_CLEAN)
	$(MAKE) -C process-launcher clean
	rm -f $(patsubst %,%_kernel.bin,$(BENCHMARKS))
	rm -f $(patsubst %,%_process.bin,$(BENCHMARKS))
	rm -f $(patsubst %,%_linux,$(BENCHMARKS))

.PHONY: $(BENCHMARKS_CLEAN)
$(BENCHMARKS_CLEAN):
	$(MAKE) -C $(patsubst %_clean,benchmarks/%,$@) clean
