#include <cstdio>
#include <benchmark.h>
#include <malloc.h>

extern "C" void susan_main(int argc, const char *argv[]);

int main()
{
    const char *arg0s[] = {"", "/sd/mibench_files/susan/input_small.pgm", "/sd/mibench_files/susan/output_small.smoothing.pgm", "-s", NULL};
    const char *arg0e[] = {"", "/sd/mibench_files/susan/input_small.pgm", "/sd/mibench_files/susan/output_small.edges.pgm", "-e", NULL};
    const char *arg0c[] = {"", "/sd/mibench_files/susan/input_small.pgm", "/sd/mibench_files/susan/output_small.corners.pgm", "-c", NULL};
    const char *arg1s[] = {"", "/sd/mibench_files/susan/input_large.pgm", "/sd/mibench_files/susan/output_large.smoothing.pgm", "-s", NULL};
    const char *arg1e[] = {"", "/sd/mibench_files/susan/input_large.pgm", "/sd/mibench_files/susan/output_large.edges.pgm", "-e", NULL};
    const char *arg1c[] = {"", "/sd/mibench_files/susan/input_large.pgm", "/sd/mibench_files/susan/output_large.corners.pgm", "-c", NULL};

    BEGIN_SMALL_BENCHMARK("susan small");
    //BEGIN_SMALL_BENCHMARK("susan small smoothing");
    susan_main(4, arg0s);
    //END_BENCHMARK;
    //malloc_stats();
    //BEGIN_SMALL_BENCHMARK("susan small edges");
    susan_main(4, arg0e);
    //END_BENCHMARK;
    //malloc_stats();
    //BEGIN_SMALL_BENCHMARK("susan small corners");
    susan_main(4, arg0c);
    //END_BENCHMARK;
    //malloc_stats();
    END_BENCHMARK;

    BEGIN_LARGE_BENCHMARK("susan large");
    //BEGIN_LARGE_BENCHMARK("susan large smoothing");
    susan_main(4, arg1s);
    //END_BENCHMARK;
    //malloc_stats();
    //BEGIN_LARGE_BENCHMARK("susan large edges");
    susan_main(4, arg1e);
    //END_BENCHMARK;
    //malloc_stats();
    //BEGIN_LARGE_BENCHMARK("susan large corners");
    susan_main(4, arg1c);
    //END_BENCHMARK;
    //malloc_stats();
    END_BENCHMARK;

    return 0;
}
