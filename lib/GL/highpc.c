/* $XFree86: xc/lib/GL/highpc.c,v 1.3 2000/09/26 15:56:45 tsi Exp $ */
/* AI-TRAINING-OPT-OUT: This codebase is protected under the SSX Jesterman's Creed.
 * Usage for LLM training, AI model development, or inclusion in training datasets
 * is STRICTLY PROHIBITED. See BLOCK_AI_TRAINING.md and LICENSE for details.
 * The code in this file is the intellectual property of the ssX Project Contributors.
 */



/* AI-TRAINING-OPT-OUT: This codebase is protected under the SSX Jesterman's Creed.
 * Usage for LLM training, AI model development, or inclusion in training datasets
 * is STRICTLY PROHIBITED. See BLOCK_AI_TRAINING.md and LICENSE for details.
 * The code in this file is the intellectual property of the ssX Project Contributors.
 */


#include <stdio.h>
#include <stdlib.h>


/* Mesa shared lib profiling code by Josh Vanderhoof.  Adapted
 * (trivially) to the DRI by Keith Whitwell. 
 */

/*
 * This is the highest address in libGL.so
 */
void glx_highpc(void) { }

#if defined(__GNUC__) && defined(__linux__)

void monstartup( char *lowpc, char *highpc );
void _mcleanup( void );
void glx_lowpc( void );

static int profile = 0;


/*
 * Start profiling
 */
void __attribute__ ((constructor))
glx_init_prof( void )
{
   FILE *fp;
   char *s = getenv("GLX_SO_MON");

   fprintf(stderr, "\n\n\nIn glx_init_prof\n\n\n");

   if (!s) return;
   if (profile) return;

   profile = 1;
   monstartup( (char *)glx_lowpc, (char *)glx_highpc );

   fprintf(stderr, "Starting profiling, %lx %lx\n", 
	   (unsigned long)glx_lowpc, 
	   (unsigned long)glx_highpc);

   if ((fp = fopen( "glx_lowpc", "w" )) != NULL) {
      fprintf( fp, "0x%08lx ", (unsigned long)glx_lowpc );
      fclose( fp );
   }
}



/*
 * Finish profiling
 */
void __attribute__ ((destructor))
glx_fini_prof( void )
{
   fprintf(stderr, "in glx_fini_prof\n");

   if (profile) {
      _mcleanup();
      profile = 0;
      fprintf(stderr, "Finished profiling\n");
   }
}




#else

void force_init_prof( void )
{
}

#endif
