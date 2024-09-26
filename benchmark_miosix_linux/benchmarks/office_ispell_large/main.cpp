#include <cstdio>
#include <benchmark.h>
#include <argv_simulation.h>
#include <unistd.h>

extern "C" int ispell_main(int argc, char *argv[], FILE *in, FILE *out);

int main()
{
    if (chdir("/sd/mibench_files/ispell")) {
        printf("could not change directory\n");
        return 1;
    }

    {
        const char *rawArgs[] = {"ispell", "-a", "-d", "americanmed+", NULL};
        WritableArguments args(rawArgs);
        FILE *in = fopen("large.txt", "r");
        if (!in)
            return -1;
        FILE *out = fopen("output_large.txt", "w");
        if (!out)
            return -1;
        BEGIN_LARGE_BENCHMARK("ispell large");
        ispell_main(args.argc, args.argv, in, out);
        fclose(in);
        fclose(out);
        END_BENCHMARK;
    }

    return 0;
}
