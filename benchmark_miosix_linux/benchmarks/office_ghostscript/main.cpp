#include <cstdio>
#include <unistd.h>
#include <setjmp.h>
#include <benchmark.h>
#ifndef MIBENCH_PROCESS_MODE
#include <util/util.h>
#endif //MIBENCH_PROCESS_MODE

extern "C" int gs_main(int argc, const char *argv[]);

jmp_buf exitPath;

extern "C" void miosix_exit(int ec)
{
    longjmp(exitPath,1);
}

int main()
{
    #ifndef MIBENCH_PROCESS_MODE
    miosix::MemoryProfiling::print();
    #endif //MIBENCH_PROCESS_MODE
    
//     puts("type enter");
//     getchar();

    chdir("/sd/mibench_files/ghostscript/resources");
    
    const char *arg0[] = {"", "-sDEVICE=ppm", "-dNOPAUSE", "-q", "-sOutputFile=/sd/mibench_files/ghostscript/output_small.ppm", "--", "/sd/mibench_files/ghostscript/small.ps", NULL};

    BEGIN_SMALL_BENCHMARK("ghostscript small");
    if(setjmp(exitPath)==0) gs_main(7, arg0);
    END_BENCHMARK;
    
    #ifndef MIBENCH_PROCESS_MODE
    miosix::MemoryProfiling::print();
    #endif //MIBENCH_PROCESS_MODE
    
    const char *arg1[] = {"", "-sDEVICE=ppm", "-dNOPAUSE", "-q", "-sOutputFile=/sd/mibench_files/ghostscript/output_large.ppm", "--", "/sd/mibench_files/ghostscript/large.ps", NULL};

    BEGIN_LARGE_BENCHMARK("ghostscript large");
    if(setjmp(exitPath)==0) gs_main(7, arg1);
    END_BENCHMARK;
    
    #ifndef MIBENCH_PROCESS_MODE
    miosix::MemoryProfiling::print();
    #endif //MIBENCH_PROCESS_MODE
}
