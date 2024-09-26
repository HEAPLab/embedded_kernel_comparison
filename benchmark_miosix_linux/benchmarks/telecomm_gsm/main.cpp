#include <cstdio>
#include <benchmark.h>

extern "C" int toast_main(int ac, char *av[]);

int main()
{
    char *arg0e[] = {"toast", "-fps", "/sd/mibench_files/gsm/small.au", "/sd/mibench_files/gsm/output_small.encode.gsm", NULL};
    char *arg0d[] = {"untoast", "-fps", "/sd/mibench_files/gsm/small.au.run.gsm", "/sd/mibench_files/gsm/output_small.decode.run", NULL};
    char *arg1e[] = {"toast", "-fps", "/sd/mibench_files/gsm/large.au", "/sd/mibench_files/gsm/output_large.encode.gsm", NULL};
    char *arg1d[] = {"untoast", "-fps", "/sd/mibench_files/gsm/large.au.run.gsm", "/sd/mibench_files/gsm/output_large.decode.run", NULL};

    BEGIN_SMALL_BENCHMARK("gsm small");
    //BEGIN_SMALL_BENCHMARK("gsm toast small");
    toast_main(4, arg0e);
    //END_BENCHMARK;
    //BEGIN_SMALL_BENCHMARK("gsm untoast small");
    toast_main(4, arg0d);
    //END_BENCHMARK;
    END_BENCHMARK;

    BEGIN_LARGE_BENCHMARK("gsm large");
    //BEGIN_LARGE_BENCHMARK("gsm toast large");
    toast_main(4, arg1e);
    //END_BENCHMARK;
    //BEGIN_LARGE_BENCHMARK("gsm untoast large");
    toast_main(4, arg1d);
    //END_BENCHMARK;
    END_BENCHMARK;
    return 0;
}
