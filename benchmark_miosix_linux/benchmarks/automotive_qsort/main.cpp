#include <stdio.h>
#include <benchmark.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

extern "C" int main_qsort_small(int argc, const char *argv[]);
extern "C" int main_qsort_large(int argc, const char *argv[]);

int main()
{
    if (chdir("/sd/mibench_files/qsort/") != 0) {
        perror("could not change directory");
        return 1;
    }
    const char *arg0[] = {"", "input_small.dat", NULL};
    const char *arg1[] = {"", "input_large.dat", NULL};

    close(1);
    int fd=open("output_small.txt",O_WRONLY|O_CREAT,0666);
    if(fd!=1) dup(fd);
    BEGIN_SMALL_BENCHMARK("qsort small");
    main_qsort_small(2, arg0);
    fflush(stdout);
    close(1);
    if(fd!=1) close(fd);
    END_BENCHMARK;

    fd=open("output_large.txt",O_WRONLY|O_CREAT,0666);
    if(fd!=1) dup(fd);
    BEGIN_LARGE_BENCHMARK("qsort large");
    main_qsort_large(2, arg1);
    fflush(stdout);
    close(1);
    if(fd!=1) close(fd);
    END_BENCHMARK;
    dup2(2,1); //Restore stdout
}
