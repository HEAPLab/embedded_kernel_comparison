#include <cstdio>
#include <benchmark.h>
#include <unistd.h>
#include <termios.h>
#include <sys/ioctl.h>

extern "C" int pbmsrch_small_main(void);
extern "C" int pbmsrch_large_main(void);

int main()
{
    BEGIN_SMALL_BENCHMARK("stringsearch small");
    pbmsrch_small_main();
    fflush(stdout);
    #ifdef __linux__
    //Linux cheats with buffering, without this call the execution time is lower
    //than the theoretical minimum to write as much characters through the
    //serial port
    tcdrain(fileno(stdout));
    #endif
    END_BENCHMARK;

    BEGIN_LARGE_BENCHMARK("stringsearch large");
    pbmsrch_large_main();
    fflush(stdout);
    #ifdef __linux__
    //Linux cheats with buffering, without this call the execution time is lower
    //than the theoretical minimum to write as much characters through the
    //serial port
    tcdrain(fileno(stdout));
    #endif
    END_BENCHMARK;
    return 0;
}
