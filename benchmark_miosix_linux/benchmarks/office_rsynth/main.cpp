#include <cstdio>
#include <benchmark.h>
#include <argv_simulation.h>
#include <unistd.h>
#include <malloc.h>

extern "C" int rsynth_main(int argc, char *argv[]);

int main()
{
    if (chdir("/sd/mibench_files/rsynth")) {
        printf("could not change directory\n");
        return 1;
    }

    {
        const char *rawArgs[] = {"rsynth", "-q", "-o", "small_output.au", "smallinput.txt", NULL};
        WritableArguments args(rawArgs);
        BEGIN_SMALL_BENCHMARK("rsynth small");
        rsynth_main(args.argc, args.argv);
        END_BENCHMARK;
    }

    {
        const char *rawArgs[] = {"rsynth", "-q", "-o", "large_output.au", "largeinput.txt", NULL};
        WritableArguments args(rawArgs);
        BEGIN_LARGE_BENCHMARK("rsynth large");
        rsynth_main(args.argc, args.argv);
        END_BENCHMARK;
    }

    return 0;
}
