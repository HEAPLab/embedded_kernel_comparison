#include <cstdio>
#include <unistd.h>
#include <setjmp.h>
#include <benchmark.h>
#ifndef MIBENCH_PROCESS_MODE
#include <util/util.h>
#endif //MIBENCH_PROCESS_MODE

extern "C" int tiffdither_main(int argc, const char *argv[]);
extern "C" int tiffdither_main(int argc, const char *argv[]);

int main()
{
    #ifndef MIBENCH_PROCESS_MODE
    miosix::MemoryProfiling::print();
    #endif //MIBENCH_PROCESS_MODE
    
//     puts("type enter");
//     getchar();
    
    const char *args0[]={"", "-c", "g4", "/sd/mibench_files/tiff/smallbw.tif", "/sd/mibench_files/tiff/output_smalldither.tif", NULL};

    BEGIN_SMALL_BENCHMARK("tiffdither small");
	tiffdither_main(5,args0);
    END_BENCHMARK;
    
    #ifndef MIBENCH_PROCESS_MODE
    miosix::MemoryProfiling::print();
    #endif //MIBENCH_PROCESS_MODE
    
    const char *args1[]={"", "-c", "g4", "/sd/mibench_files/tiff/largebw.tif", "/sd/mibench_files/tiff/output_largedither.tif", NULL};
    
    BEGIN_LARGE_BENCHMARK("tiffdither large");
	tiffdither_main(5,args1);
    END_BENCHMARK;
    
    #ifndef MIBENCH_PROCESS_MODE
    miosix::MemoryProfiling::print();
    #endif //MIBENCH_PROCESS_MODE
}
