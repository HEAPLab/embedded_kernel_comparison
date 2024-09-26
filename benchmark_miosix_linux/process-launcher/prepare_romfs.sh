#!/usr/bin/env bash

rm -rf romfs
mkdir -p romfs
for bench in "$@"; do
    bench_root=../benchmarks/$bench
    make -C ${bench_root} process || exit 1
    if [[ -e ${bench_root}/romfs ]]; then
        cp -R ${bench_root}/romfs/ romfs
    fi
    cp ${bench_root}/${bench} romfs/${bench}.elf
done
