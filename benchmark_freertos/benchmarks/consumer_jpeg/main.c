#include <stdio.h>
#include <unistd.h>
#include <setjmp.h>
#include <benchmark.h>
#include "fake_stdio.h"

int cjpeg_main(int argc, const char *argv[]);
int djpeg_main(int argc, const char *argv[]);

void freertos_main(void)
{   
//     puts("type enter");
//     getchar();
    
    const char *args0a[]={"", "-dct", "int", "-progressive", "-opt", "-outfile", "mibench_files/jpeg/output_small_encode.jpeg", "mibench_files/jpeg/input_small.ppm", NULL};
    const char *args0b[]={"", "-dct", "int", "-ppm", "-outfile", "mibench_files/jpeg/output_small_decode.ppm", "mibench_files/jpeg/input_small.jpg", NULL};

    BEGIN_SMALL_BENCHMARK("jpeg small");
	cjpeg_main(8,args0a);
	djpeg_main(7,args0b);
    END_BENCHMARK;
    
    const char *args1a[]={"", "-dct", "int", "-progressive", "-opt", "-outfile", "mibench_files/jpeg/output_large_encode.jpeg", "mibench_files/jpeg/input_large.ppm", NULL};
    const char *args1b[]={"", "-dct", "int", "-ppm", "-outfile", "mibench_files/jpeg/output_large_decode.ppm", "mibench_files/jpeg/input_large.jpg", NULL};

    BEGIN_LARGE_BENCHMARK("jpeg large");
	cjpeg_main(8,args1a);
	djpeg_main(7,args1b);
    END_BENCHMARK;
}
