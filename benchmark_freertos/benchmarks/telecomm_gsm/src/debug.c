/*
 * Copyright 1992 by Jutta Degener and Carsten Bormann, Technische
 * Universitaet Berlin.  See the accompanying file "COPYRIGHT" for
 * details.  THERE IS ABSOLUTELY NO WARRANTY FOR THIS SOFTWARE.
 */

/* $Header: /home/mguthaus/.cvsroot/mibench/telecomm/gsm/src/debug.c,v 1.1.1.1 2000/11/06 19:54:25 mguthaus Exp $ */

#include "private.h"

#ifndef	NDEBUG

/* If NDEBUG _is_ defined and no debugging should be performed,
 * calls to functions in this module are #defined to nothing
 * in private.h.
 */

#include <stdio.h>
#include "fake_stdio.h"
#include "proto.h"

void gsm_debug_words P4( (name, from, to, ptr), 
	char 	      * name,
	int		from,
	int		to,
	word		* ptr)
{
	int 	nprinted = 0;

	printf( "%s [%d .. %d]: ", name, from, to );
	while (from <= to) {
		printf( "%d ", ptr[ from ] );
		from++;
		if (nprinted++ >= 7) {
			nprinted = 0;
			if (from < to) putchar('\n');
		}
	}
	putchar('\n');
}

void gsm_debug_longwords P4( (name, from, to, ptr),
	char 	      * name,
	int		from,
	int		to,
	longword      * ptr)
{
	int 	nprinted = 0;

	printf( "%s [%d .. %d]: ", name, from, to );
	while (from <= to) {

		printf( "%d ", ptr[ from ] );
		from++;
		if (nprinted++ >= 7) {
			nprinted = 0;
			if (from < to) putchar('\n');
		}
	}
	putchar('\n');
}

void gsm_debug_longword P2(  (name, value),
	char		* name,
	longword	  value	)
{
	printf( "%s: %d\n", name, (long)value );
}

void gsm_debug_word P2(  (name, value),
	char	* name,
	word	  value	)
{
	printf( "%s: %d\n", name, (long)value);
}

#endif
