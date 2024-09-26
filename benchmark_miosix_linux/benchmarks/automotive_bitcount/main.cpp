#include <stdio.h>
#include <benchmark.h>

extern "C" int main_bitcnts(int argc, const char *argv[]);

int main()
{
    const char *arg0[] = {"", "75000", NULL};
    const char *arg1[] = {"", "1125000", NULL};

    BEGIN_SMALL_BENCHMARK("bitcnts small");
    main_bitcnts(2, arg0);
    END_BENCHMARK;

    BEGIN_LARGE_BENCHMARK("bitcnts large");
    main_bitcnts(2, arg1);
    END_BENCHMARK;
}
