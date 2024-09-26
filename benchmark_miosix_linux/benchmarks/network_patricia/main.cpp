#include <cstdio>
#include <benchmark.h>
#include <unistd.h>

extern "C" int patricia_main(int argc, const char *argv[]);

int main()
{
    if (chdir("/sd/mibench_files/patricia/") != 0) {
        perror("could not change directory");
        return 1;
    }
    const char *arg0[] = {"", "small.udp", NULL};
    const char *arg1[] = {"", "large.udp", NULL};

    BEGIN_SMALL_BENCHMARK("patricia small");
    patricia_main(2, arg0);
    END_BENCHMARK;

    BEGIN_LARGE_BENCHMARK("patricia large");
    patricia_main(2, arg1);
    END_BENCHMARK;
    return 0;
}
