BENCHMARKS:=\
automotive_basicmath \
automotive_bitcount \
automotive_susan \
consumer_jpeg \
consumer_lame \
network_patricia \
office_stringsearch \
security_blowfish \
security_rijndael \
security_sha \
telecomm_crc32 \
telecomm_fft \
telecomm_gsm \
test_kernel_blinker

.PHONY: all
all:
	for b in $(BENCHMARKS); do \
	  $(MAKE) -C "benchmarks/$$b" || exit 1; \
	  cp "benchmarks/$$b/main.bin" "$$b.bin"; \
	done

.phony: clean
clean:
	for b in $(BENCHMARKS); do \
	  $(MAKE) -C "benchmarks/$$b" clean; \
	  rm -f "$$b.bin"; \
	done
