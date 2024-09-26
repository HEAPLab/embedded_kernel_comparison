#include <cstdio>
#include <unistd.h>
#include <setjmp.h>
#include <benchmark.h>
#ifndef MIBENCH_PROCESS_MODE
#include <util/util.h>
#endif //MIBENCH_PROCESS_MODE

extern "C" int mad_main(int argc, const char *argv[]);

int main()
{
    if (chdir("/sd/mibench_files/mad")) {
        printf("could not change directory\n");
        return 1;
    }

    #ifndef MIBENCH_PROCESS_MODE
    miosix::MemoryProfiling::print();
    #endif //MIBENCH_PROCESS_MODE
    
    //puts("type enter");
    //getchar();
    
    const char *args0[]={"", "--time=4", "--output=wave:output_small.wav", "-v", "small.mp3", NULL};

    BEGIN_SMALL_BENCHMARK("mad small");
	mad_main(5,args0);
    END_BENCHMARK;
    
    #ifndef MIBENCH_PROCESS_MODE
    miosix::MemoryProfiling::print();
    #endif //MIBENCH_PROCESS_MODE
}
