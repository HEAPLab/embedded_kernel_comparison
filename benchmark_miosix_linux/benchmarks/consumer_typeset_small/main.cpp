#include <cstdio>
#include <benchmark.h>
#include <argv_simulation.h>
#include <unistd.h>

extern "C" int lout_main(int argc, char *argv[]);

int main()
{
    if (chdir("/sd/mibench_files/typeset")) {
        printf("could not change directory\n");
        return 1;
    }
    
//     puts("type enter");
//     getchar();

    {
        const char *rawArgs[] = {"lout", "-I", "include", "-D", "data", "-F", "font", "-C", "maps", "-H", "hyph", "-o", "output_small.ps", "small.lout", NULL};
        WritableArguments args(rawArgs);
        BEGIN_SMALL_BENCHMARK("typeset small");
        lout_main(args.argc, args.argv);
        END_BENCHMARK;
    }
    
    unlink("lout.li");
    unlink("lout.lix");
    unlink("small.lout.ld");
    unlink("small.lout.ldx");
    
    return 0;
}
