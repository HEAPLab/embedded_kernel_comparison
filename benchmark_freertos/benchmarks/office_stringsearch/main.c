#include <stdio.h>
#include <benchmark.h>
#include <unistd.h>
#include "fake_stdio.h"

int pbmsrch_small_main(void);
int pbmsrch_large_main(void);

FILE *output;

void freertos_main(void)
{
    BEGIN_SMALL_BENCHMARK("stringsearch small");
    pbmsrch_small_main();
    END_BENCHMARK;

    BEGIN_LARGE_BENCHMARK("stringsearch large");
    pbmsrch_large_main();
    END_BENCHMARK;
}
