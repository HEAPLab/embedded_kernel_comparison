#include <cstdio>
#include <benchmark.h>

extern "C" int sha_main(int argc, const char *argv[]);

int main()
{
    const char *arg0[] = {"", "/sd/mibench_files/sha/input_small.asc", NULL};
    const char *arg1[] = {"", "/sd/mibench_files/sha/input_large.asc", NULL};

    BEGIN_SMALL_BENCHMARK("sha small");
    sha_main(2, arg0);
    END_BENCHMARK;

    BEGIN_LARGE_BENCHMARK("sha large");
    sha_main(2, arg1);
    END_BENCHMARK;
    return 0;
}
