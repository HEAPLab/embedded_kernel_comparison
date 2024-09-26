#include <cstdio>
#include <unistd.h>
#include <setjmp.h>
#include <benchmark.h>
#ifndef MIBENCH_PROCESS_MODE
#include <util/util.h>
#endif //MIBENCH_PROCESS_MODE

extern "C" int tiff2rgba_main(int argc, const char *argv[]);
extern "C" int tiff2rgba_main(int argc, const char *argv[]);

int main()
{
    #ifndef MIBENCH_PROCESS_MODE
    miosix::MemoryProfiling::print();
    #endif //MIBENCH_PROCESS_MODE
    
    //puts("type enter");
    //getchar();
    
    const char *args0[]={"", "-c", "none", "/sd/mibench_files/tiff/small.tif", "/sd/mibench_files/tiff/output_smallrgba.tif", NULL};

    BEGIN_SMALL_BENCHMARK("tiff2rgba small");
	tiff2rgba_main(5,args0);
    END_BENCHMARK;
    
    #ifndef MIBENCH_PROCESS_MODE
    miosix::MemoryProfiling::print();
    #endif //MIBENCH_PROCESS_MODE
    
    //TOO BIG
    //const char *args1[]={"", "-c", "none", "/sd/mibench_files/tiff/large.tif", "/sd/mibench_files/tiff/output_largergba.tif", NULL};
    //     
    //BEGIN_LARGE_BENCHMARK("tiff2rgba large");
    //tiff2rgba_main(5,args1);
    //END_BENCHMARK;
    
    //#ifndef MIBENCH_PROCESS_MODE
    //miosix::MemoryProfiling::print();
    //#endif //MIBENCH_PROCESS_MODE
}
