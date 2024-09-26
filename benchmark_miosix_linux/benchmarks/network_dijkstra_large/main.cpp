#include <cstdio>
#include <benchmark.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

extern "C" int dijkstra_large_main(int argc, const char *argv[]);

int main()
{
    if (chdir("/sd/mibench_files/dijkstra/") != 0) {
        perror("could not change directory");
        return 1;
    }
    const char *arg0[] = {"", "input.dat", NULL};

    close(1);
    int fd=open("output_large.txt",O_WRONLY|O_CREAT,0666);
    if(fd!=1) dup(fd);
    BEGIN_LARGE_BENCHMARK("dijkstra large");
    dijkstra_large_main(2, arg0);
    fflush(stdout);
    close(1);
    if(fd!=1) close(fd);
    END_BENCHMARK;
    dup2(2,1); //Restore stdout
    return 0;
}
