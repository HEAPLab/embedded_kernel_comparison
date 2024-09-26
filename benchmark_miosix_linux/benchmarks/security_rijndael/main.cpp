#include <cstdio>
#include <benchmark.h>

extern "C" int rijndael_main(int argc, const char *argv[]);

int main()
{
    const char *arg0enc[] = {
        "", 
        "/sd/mibench_files/rijndael/input_small.asc", 
        "/sd/mibench_files/rijndael/output_small.enc", 
        "e", 
        "1234567890abcdeffedcba09876543211234567890abcdeffedcba0987654321", 
        NULL};
    const char *arg0dec[] = {
        "", 
        "/sd/mibench_files/rijndael/output_small.enc", 
        "/sd/mibench_files/rijndael/output_small.dec", 
        "d", 
        "1234567890abcdeffedcba09876543211234567890abcdeffedcba0987654321", 
        NULL};

    const char *arg1enc[] = {
        "", 
        "/sd/mibench_files/rijndael/input_large.asc", 
        "/sd/mibench_files/rijndael/output_large.enc", 
        "e", 
        "1234567890abcdeffedcba09876543211234567890abcdeffedcba0987654321", 
        NULL};
    const char *arg1dec[] = {
        "", 
        "/sd/mibench_files/rijndael/output_large.enc", 
        "/sd/mibench_files/rijndael/output_large.dec", 
        "d", 
        "1234567890abcdeffedcba09876543211234567890abcdeffedcba0987654321", 
        NULL};

    BEGIN_SMALL_BENCHMARK("rijndael small");
    //BEGIN_SMALL_BENCHMARK("rijndael small encode");
    rijndael_main(5, arg0enc);
    //END_BENCHMARK;
    //BEGIN_SMALL_BENCHMARK("rijndael small decode");
    rijndael_main(5, arg0dec);
    //END_BENCHMARK;
    END_BENCHMARK;

    BEGIN_LARGE_BENCHMARK("rijndael large");
    //BEGIN_LARGE_BENCHMARK("rijndael large encode");
    rijndael_main(5, arg1enc);
    //END_BENCHMARK;
    //BEGIN_LARGE_BENCHMARK("rijndael large decode");
    rijndael_main(5, arg1dec);
    //END_BENCHMARK;
    END_BENCHMARK;

    return 0;
}
