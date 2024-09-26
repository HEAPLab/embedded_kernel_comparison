#include <stdio.h>
#include <benchmark.h>
#include <unistd.h>
#include "fake_stdio.h"

int patricia_main(int argc, const char *argv[]);

void freertos_main(void)
{
    const char *arg0[] = {"", "mibench_files/patricia/small.udp", NULL};
    const char *arg1[] = {"", "mibench_files/patricia/large.udp", NULL};

    BEGIN_SMALL_BENCHMARK("patricia small");
    patricia_main(2, arg0);
    END_BENCHMARK;

    BEGIN_LARGE_BENCHMARK("patricia large");
    patricia_main(2, arg1);
    END_BENCHMARK;
    return 0;
}
