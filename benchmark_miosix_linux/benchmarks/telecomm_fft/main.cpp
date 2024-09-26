#include <cstdio>
#include <benchmark.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

extern "C" int fft_main(int argc, const char *argv[]);

int main()
{
    if (chdir("/sd/mibench_files/") != 0) {
        perror("could not change directory");
        return 1;
    }
    const char *arg0[] = {"", "4", "4096", NULL};
    const char *arg1[] = {"", "4", "8192", "-i", NULL};
    const char *arg2[] = {"", "8", "32768", NULL};
    const char *arg3[] = {"", "8", "32768", "-i", NULL};

    close(1);
    int fd=open("fft_output_small.txt",O_WRONLY|O_CREAT,0666);
    if(fd!=1) dup(fd);
    BEGIN_SMALL_BENCHMARK("fft small");
    fft_main(3, arg0);
    //END_BENCHMARK;
    //BEGIN_SMALL_BENCHMARK("fft small inverse");
    fft_main(4, arg1);
    fflush(stdout);
    close(1);
    if(fd!=1) close(fd);
    END_BENCHMARK;

    fd=open("fft_output_large.txt",O_WRONLY|O_CREAT,0666);
    if(fd!=1) dup(fd);
    BEGIN_LARGE_BENCHMARK("fft large");
    fft_main(3, arg2);
    //END_BENCHMARK;
    //BEGIN_LARGE_BENCHMARK("fft large inverse");
    fft_main(4, arg3);
    fflush(stdout);
    close(1);
    if(fd!=1) close(fd);
    END_BENCHMARK;
    dup2(2,1); //Restore stdout
    
    return 0;
}
