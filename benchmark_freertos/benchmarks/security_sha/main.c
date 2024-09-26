#include <stdio.h>
#include <benchmark.h>
#include "fake_stdio.h"

int sha_main(int argc, const char *argv[]);

void freertos_main(void)
{
    const char *arg0[] = {"", "mibench_files/sha/input_small.asc", NULL};
    const char *arg1[] = {"", "mibench_files/sha/input_large.asc", NULL};

    BEGIN_SMALL_BENCHMARK("sha small");
    sha_main(2, arg0);
    END_BENCHMARK;

    BEGIN_LARGE_BENCHMARK("sha large");
    sha_main(2, arg1);
    END_BENCHMARK;
}
