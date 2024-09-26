#include <cstdio>
#include <unistd.h>
#include <setjmp.h>
#include <benchmark.h>
#ifndef MIBENCH_PROCESS_MODE
#include <util/util.h>
#endif //MIBENCH_PROCESS_MODE

extern "C" int cjpeg_main(int argc, const char *argv[]);
extern "C" int djpeg_main(int argc, const char *argv[]);

int main()
{
    #ifndef MIBENCH_PROCESS_MODE
    miosix::MemoryProfiling::print();
    #endif //MIBENCH_PROCESS_MODE
    
//     puts("type enter");
//     getchar();
    
    const char *args0a[]={"", "-dct", "int", "-progressive", "-opt", "-outfile", "/sd/mibench_files/jpeg/output_small_encode.jpeg", "/sd/mibench_files/jpeg/input_small.ppm", NULL};
    const char *args0b[]={"", "-dct", "int", "-ppm", "-outfile", "/sd/mibench_files/jpeg/output_small_decode.ppm", "/sd/mibench_files/jpeg/input_small.jpg", NULL};

    BEGIN_SMALL_BENCHMARK("jpeg small");
	cjpeg_main(8,args0a);
	djpeg_main(7,args0b);
    END_BENCHMARK;
    
    #ifndef MIBENCH_PROCESS_MODE
    miosix::MemoryProfiling::print();
    #endif //MIBENCH_PROCESS_MODE
    
    const char *args1a[]={"", "-dct", "int", "-progressive", "-opt", "-outfile", "/sd/mibench_files/jpeg/output_large_encode.jpeg", "/sd/mibench_files/jpeg/input_large.ppm", NULL};
    const char *args1b[]={"", "-dct", "int", "-ppm", "-outfile", "/sd/mibench_files/jpeg/output_large_decode.ppm", "/sd/mibench_files/jpeg/input_large.jpg", NULL};

    BEGIN_LARGE_BENCHMARK("jpeg large");
	cjpeg_main(8,args1a);
	djpeg_main(7,args1b);
    END_BENCHMARK;
    
    #ifndef MIBENCH_PROCESS_MODE
    miosix::MemoryProfiling::print();
    #endif //MIBENCH_PROCESS_MODE
}
