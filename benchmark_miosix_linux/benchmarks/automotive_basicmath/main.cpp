#include <stdio.h>
#include <benchmark.h>

extern "C" int main_small(void);
extern "C" int main_large(void);

int main()
{
    BEGIN_SMALL_BENCHMARK("basicmath small");
    main_small();
    END_BENCHMARK;

    BEGIN_LARGE_BENCHMARK("basicmath large");
    main_large();
    END_BENCHMARK;
}
