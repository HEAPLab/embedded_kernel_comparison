#include <stdio.h>
#include <benchmark.h>

int blowfish_main(int argc, const char *argv[]);

void freertos_main(void)
{
    static const char *arg0e[] = {"", "e", "mibench_files/blowfish/input_small.asc", "mibench_files/blowfish/output_small.enc", "1234567890abcdeffedcba0987654321", NULL};
    static const char *arg0d[] = {"", "d", "mibench_files/blowfish/output_small.enc", "mibench_files/blowfish/output_small.asc", "1234567890abcdeffedcba0987654321", NULL};
    static const char *arg1e[] = {"", "e", "mibench_files/blowfish/input_large.asc", "mibench_files/blowfish/output_large.enc", "1234567890abcdeffedcba0987654321", NULL};
    static const char *arg1d[] = {"", "d", "mibench_files/blowfish/output_large.enc", "mibench_files/blowfish/output_large.asc", "1234567890abcdeffedcba0987654321", NULL};

    BEGIN_SMALL_BENCHMARK("blowfish small");
    //BEGIN_SMALL_BENCHMARK("blowfish encode small");
    blowfish_main(5, arg0e);
    //END_BENCHMARK;
    //BEGIN_SMALL_BENCHMARK("blowfish decode small");
    blowfish_main(5, arg0d);
    //END_BENCHMARK;
    END_BENCHMARK;

    BEGIN_LARGE_BENCHMARK("blowfish large");
    //BEGIN_LARGE_BENCHMARK("blowfish encode large");
    blowfish_main(5, arg1e);
    //END_BENCHMARK;
    //BEGIN_LARGE_BENCHMARK("blowfish decode large");
    blowfish_main(5, arg1d);
    //END_BENCHMARK;
    END_BENCHMARK;
}
