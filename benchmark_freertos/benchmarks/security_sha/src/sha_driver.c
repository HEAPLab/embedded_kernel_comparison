/* NIST Secure Hash Algorithm */

#include <stdlib.h>
#include <stdio.h>
#include "fake_stdio.h"
#define FATFS_LONG LONG
#define LONG BENCHMARK_LONG
#include <string.h>
#include <time.h>
#include "sha.h"

//int main(int argc, char **argv)
int sha_main(int argc, const char *argv[])
{
    FILE *fin;
    SHA_INFO sha_info;

    if (argc < 2) {
        printf("error: stdin input doesn't work\n");
	//fin = stdin;
	//sha_stream(&sha_info, fin);
	//sha_print(&sha_info);
    } else {
	while (--argc) {
	    fin = fopen(*(++argv), "rb");
	    if (fin == NULL) {
		printf("error opening %s for reading\n", *argv);
	    } else {
		sha_stream(&sha_info, fin);
		sha_print(&sha_info);
		fclose(fin);
	    }
	}
    }
    return(0);
}
