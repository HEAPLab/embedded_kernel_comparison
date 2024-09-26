#include <stdio.h>
#include "fake_stdio.h"
#include <benchmark.h>
#include <unistd.h>

int fft_main(int argc, const char *argv[]);

FILE *output;

void freertos_main(void)
{
    const char *arg0[] = {"", "4", "4096", NULL};
    const char *arg1[] = {"", "4", "8192", "-i", NULL};
    const char *arg2[] = {"", "8", "32768", NULL};
    const char *arg3[] = {"", "8", "32768", "-i", NULL};

    output = fopen("mibench_files/fft_output_small.txt", "w");
    BEGIN_SMALL_BENCHMARK("fft small");
    fft_main(3, arg0);
    //END_BENCHMARK;
    //BEGIN_SMALL_BENCHMARK("fft small inverse");
    fft_main(4, arg1);
    fclose(output);
    END_BENCHMARK;

    output = fopen("mibench_files/fft_output_large.txt", "w");
    BEGIN_LARGE_BENCHMARK("fft large");
    fft_main(3, arg2);
    //END_BENCHMARK;
    //BEGIN_LARGE_BENCHMARK("fft large inverse");
    fft_main(4, arg3);
    fclose(output);
    END_BENCHMARK;
}
