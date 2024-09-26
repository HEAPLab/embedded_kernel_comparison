#include <stdio.h>
#include <benchmark.h>
#include <unistd.h>
#include "fake_stdio.h"

int lame_main(int argc, char *argv[]);

void freertos_main(void)
{
    {
        char arg1[] = "lame";
        char arg2[] = "mibench_files/lame/small.wav";
        char arg3[] = "mibench_files/lame/output_small.mp3";
        char *rawArgs[] = {arg1, arg2, arg3, NULL};
        BEGIN_SMALL_BENCHMARK("lame small");
        lame_main(3, rawArgs);
        END_BENCHMARK;
    }

    {
        char arg1[] = "lame";
        char arg2[] = "mibench_files/lame/large.wav";
        char arg3[] = "mibench_files/lame/output_large.mp3";
        char *rawArgs[] = {arg1, arg2, arg3, NULL};
        BEGIN_LARGE_BENCHMARK("lame large");
        lame_main(3, rawArgs);
        END_BENCHMARK;
    }
    return 0;
}
