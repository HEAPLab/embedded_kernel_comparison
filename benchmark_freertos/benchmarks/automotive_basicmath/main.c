#include <stdio.h>
#include <benchmark.h>

int main_small(void);
int main_large(void);

void freertos_main(void)
{
    BEGIN_SMALL_BENCHMARK("basicmath small");
    main_small();
    END_BENCHMARK;

    BEGIN_LARGE_BENCHMARK("basicmath large");
    main_large();
    END_BENCHMARK;
}
