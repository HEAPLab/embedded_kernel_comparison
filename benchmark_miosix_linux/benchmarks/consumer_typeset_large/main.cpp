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
        const char *rawArgs[]={"lout", "-I", "include", "-D", "data", "-F", "font", "-C", "maps", "-H", "hyph", "-o", "output_large.ps", "large.lout", NULL};
        WritableArguments args(rawArgs);
        BEGIN_LARGE_BENCHMARK("typeset large");
        lout_main(args.argc, args.argv);
        END_BENCHMARK;
    }
    
    unlink("lout.li");
    unlink("lout.lix");
    unlink("large.lout.ld");
    unlink("large.lout.ldx");
    
    return 0;
}
