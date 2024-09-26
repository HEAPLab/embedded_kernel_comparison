# Miosix & Linux MiBench

## Building benchmarks

Pre-compiled builds for the stm32f469_discovery board are in
the `stm32f469_images` directory.

`make` compiles binaries for all benchmarks and platforms --
Linux, Miosix kernel-mode and process-mode.

To compile for just Linux: `make all_linux`

To compile for just Miosix kernel-mode: `make all_kernel`

To compile for just Miosix process-mode: `make all_process`

To clean up build products: `make clean`

## Running the benchmarks

Prepare an SD card with the contents of the `benchmark_data_files`
directory in the root.
Then you can run the Miosix benchmarks simply by flashing the
.bin files to the internal Flash.

For Linux, also copy the *_linux binaries on the SD card, and
flash the kernel onto the board using the script in the
build_linux directory.

Under Linux, you must first mount the SD card to the /sd directory.
You cannot mount the card anywhere else otherwise the benchmarks
won't find their data files.
Then you can just run the benchmarks from the shell.
