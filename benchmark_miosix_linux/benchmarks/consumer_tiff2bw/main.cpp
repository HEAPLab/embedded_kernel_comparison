#include <cstdio>
#include <unistd.h>
#include <setjmp.h>
#include <benchmark.h>
#ifndef MIBENCH_PROCESS_MODE
#include <util/util.h>
#endif //MIBENCH_PROCESS_MODE

extern "C" int tiff2bw_main(int argc, const char *argv[]);
extern "C" int tiff2bw_main(int argc, const char *argv[]);

int main()
{
    #ifndef MIBENCH_PROCESS_MODE
    miosix::MemoryProfiling::print();
    #endif //MIBENCH_PROCESS_MODE
    
//     puts("type enter");
//     getchar();
    
    const char *args0[]={"", "/sd/mibench_files/tiff/small.tif", "/sd/mibench_files/tiff/output_smallbw.tif", NULL};

    BEGIN_SMALL_BENCHMARK("tiff2bw small");
	tiff2bw_main(3,args0);
    END_BENCHMARK;
    
    #ifndef MIBENCH_PROCESS_MODE
    miosix::MemoryProfiling::print();
    #endif //MIBENCH_PROCESS_MODE
    
    const char *args1[]={"", "/sd/mibench_files/tiff/large.tif", "/sd/mibench_files/tiff/output_largebw.tif", NULL};

    BEGIN_LARGE_BENCHMARK("tiff2bw large");
	tiff2bw_main(3,args1);
    END_BENCHMARK;
    
    #ifndef MIBENCH_PROCESS_MODE
    miosix::MemoryProfiling::print();
    #endif //MIBENCH_PROCESS_MODE
}
