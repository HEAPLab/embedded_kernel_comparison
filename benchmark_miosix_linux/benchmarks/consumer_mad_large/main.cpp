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
    
    const char *args1[]={"", "--time=30", "--output=wave:output_large.wav", "-v", "large.mp3", NULL};

    BEGIN_LARGE_BENCHMARK("mad large");
	mad_main(5,args1);
    END_BENCHMARK;
    
    #ifndef MIBENCH_PROCESS_MODE
    miosix::MemoryProfiling::print();
    #endif //MIBENCH_PROCESS_MODE
}
