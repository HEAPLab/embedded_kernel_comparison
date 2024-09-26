#include <cstdio>
#include <unistd.h>
#include <setjmp.h>
#include <benchmark.h>
#ifndef MIBENCH_PROCESS_MODE
#include <util/util.h>
#endif //MIBENCH_PROCESS_MODE

extern "C" int tiffmedian_main(int argc, const char *argv[]);
extern "C" int tiffmedian_main(int argc, const char *argv[]);

int main()
{
    #ifndef MIBENCH_PROCESS_MODE
    miosix::MemoryProfiling::print();
    #endif //MIBENCH_PROCESS_MODE
    
//     puts("type enter");
//     getchar();
    
    const char *args0[]={"", "/sd/mibench_files/tiff/small.tif", "/sd/mibench_files/tiff/output_smallmedian.tif", NULL};

    BEGIN_SMALL_BENCHMARK("tiffmedian small");
	tiffmedian_main(3,args0);
    END_BENCHMARK;
    
    #ifndef MIBENCH_PROCESS_MODE
    miosix::MemoryProfiling::print();
    #endif //MIBENCH_PROCESS_MODE
    
    const char *args1[]={"", "/sd/mibench_files/tiff/large.tif", "/sd/mibench_files/tiff/output_largemedian.tif", NULL};
    
    BEGIN_LARGE_BENCHMARK("tiffmedian large");
	tiffmedian_main(3,args1);
    END_BENCHMARK;
    
    #ifndef MIBENCH_PROCESS_MODE
    miosix::MemoryProfiling::print();
    #endif //MIBENCH_PROCESS_MODE
}
