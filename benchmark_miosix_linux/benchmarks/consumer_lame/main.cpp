#include <cstdio>
#include <benchmark.h>
#include <argv_simulation.h>
#include <unistd.h>

extern "C" int lame_main(int argc, char *argv[]);

int main()
{
    if (chdir("/sd/mibench_files/lame")) {
        printf("could not change directory\n");
        return 1;
    }

    {
        const char *rawArgs[] = {"lame", "small.wav", "output_small.mp3", NULL};
        WritableArguments args(rawArgs);
        BEGIN_SMALL_BENCHMARK("lame small");
        lame_main(args.argc, args.argv);
        END_BENCHMARK;
    }

    {
        const char *rawArgs[] = {"lame", "large.wav", "output_large.mp3", NULL};
        WritableArguments args(rawArgs);
        BEGIN_LARGE_BENCHMARK("lame large");
        lame_main(args.argc, args.argv);
        END_BENCHMARK;
    }
    return 0;
}
