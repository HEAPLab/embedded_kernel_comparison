#include <cstdio>
#include <benchmark.h>
#include <unistd.h>
#include <string.h>
#include <argv_simulation.h>

extern "C" int pgp_main(int argc, char **argv);

// Pretty good privacy? Maybe. Pretty bad code? For sure!
// Fortunately I think it has improved since 1996

int main()
{
    const char *arg0[] = {"pgp", "-sa", "-z", "this is a test", "-u", "taustin@eecs.umich.edu", "testin.txt", "austin@umich.edu", NULL};
    const char *arg1[] = {"pgp", "-z", "this is a test", "-u", "taustin@eecs.umich.edu", "testout.txt.asc", NULL};

    if (chdir("/sd/mibench_files/pgp")) {
        printf("could not change directory\n");
        return 1;
    }
    if (unlink("testin.txt.asc") == 0) {
        printf("deleted testin.txt.asc, otherwise pgp complains\n");
    } else {
        printf("testin.txt.asc not deleted (maybe it doesn't exist)\n");
    }

    WritableArguments args_encode(arg0);
    WritableArguments args_decode(arg1);

    BEGIN_SMALL_BENCHMARK("pgp");
    //BEGIN_SMALL_BENCHMARK("pgp encode");
    pgp_main(args_encode.argc, args_encode.argv);
    //END_BENCHMARK;
    //BEGIN_SMALL_BENCHMARK("pgp decode");
    pgp_main(args_decode.argc, args_decode.argv);
    //END_BENCHMARK;
    END_BENCHMARK;

    return 0;
}
