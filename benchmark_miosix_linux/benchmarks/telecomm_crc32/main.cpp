#include <cstdio>
#include <benchmark.h>

extern "C" int crc32_main(int argc, const char *argv[]);

int main()
{
    const char *arg0[] = {"", "/sd/mibench_files/adpcm/small.pcm", NULL};
    const char *arg1[] = {"", "/sd/mibench_files/adpcm/large.pcm", NULL};

    BEGIN_SMALL_BENCHMARK("crc32 small");
    crc32_main(2, arg0);
    END_BENCHMARK;

    BEGIN_LARGE_BENCHMARK("crc32 large");
    crc32_main(2, arg1);
    END_BENCHMARK;
    return 0;
}
