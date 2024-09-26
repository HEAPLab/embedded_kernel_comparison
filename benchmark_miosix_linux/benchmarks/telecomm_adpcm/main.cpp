#include <cstdio>
#include <fcntl.h>
#include <unistd.h>
#include <benchmark.h>

extern "C" void rawcaudio_main(int fd_in, int fd_out);
extern "C" void rawdaudio_main(int fd_in, int fd_out);

int main()
{
    int fd_in, fd_out, fd_in_d, fd_out_d;

    fd_in = open("/sd/mibench_files/adpcm/small.pcm", O_RDONLY);
    fd_out = open("/sd/mibench_files/adpcm/output_small.adpcm", O_WRONLY | O_CREAT);
    fd_in_d = open("/sd/mibench_files/adpcm/small.adpcm", O_RDONLY);
    fd_out_d = open("/sd/mibench_files/adpcm/output_small.pcm", O_WRONLY | O_CREAT);
    BEGIN_SMALL_BENCHMARK("adpcm small");
    //BEGIN_SMALL_BENCHMARK("adpcm encode small");
    rawcaudio_main(fd_in, fd_out);
    //END_BENCHMARK;
    //BEGIN_SMALL_BENCHMARK("adpcm decode small");
    rawdaudio_main(fd_in_d, fd_out_d);
    //END_BENCHMARK;
    close(fd_in);
    close(fd_out);
    close(fd_in_d);
    close(fd_out_d);
    END_BENCHMARK;

    fd_in = open("/sd/mibench_files/adpcm/large.pcm", O_RDONLY);
    fd_out = open("/sd/mibench_files/adpcm/output_large.adpcm", O_WRONLY | O_CREAT);
    fd_in_d = open("/sd/mibench_files/adpcm/large.adpcm", O_RDONLY);
    fd_out_d = open("/sd/mibench_files/adpcm/output_large.pcm", O_WRONLY | O_CREAT);
    BEGIN_LARGE_BENCHMARK("adpcm large");
    //BEGIN_LARGE_BENCHMARK("adpcm encode large");
    rawcaudio_main(fd_in, fd_out);
    //END_BENCHMARK;
    //BEGIN_LARGE_BENCHMARK("adpcm decode large");
    rawdaudio_main(fd_in_d, fd_out_d);
    //END_BENCHMARK;
    close(fd_in);
    close(fd_out);
    close(fd_in_d);
    close(fd_out_d);
    END_BENCHMARK;


    return 0;
}
