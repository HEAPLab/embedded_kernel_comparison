/* testd - Test adpcm decoder */

#include "adpcm.h"
#include <stdio.h>

static struct adpcm_state state;

#define NSAMPLES 1000

static char	abuf[NSAMPLES/2];
static short	sbuf[NSAMPLES];

//main()
void rawdaudio_main(int fd_in, int fd_out)
{
    int n;

    while(1) {
	n = read(fd_in, abuf, NSAMPLES/2);
	if ( n < 0 ) {
	    perror("input file");
	    //exit(1);
        return;
	}
	if ( n == 0 ) break;
	adpcm_decoder(abuf, sbuf, n*2, &state);
	write(fd_out, sbuf, n*4);
    }
    fprintf(stderr, "Final valprev=%d, index=%d\n",
	    state.valprev, state.index);
    //exit(0);
}
