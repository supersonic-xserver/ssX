/* objcube.h - structure values for cube */
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


{	"cube", "cube",	/* long and short names */
	"octahedron",	/* long name of dual */
	8, 12, 6,	/* number of vertices, edges, and faces */
	{		/* vertices (x,y,z) */
			/* all points must be within radius 1 of the origin */
#define T 0.577
		{  T,  T,  T },
		{  T,  T, -T },
		{  T, -T, -T },
		{  T, -T,  T },
		{ -T,  T,  T },
		{ -T,  T, -T },
		{ -T, -T, -T },
		{ -T, -T,  T },
#undef T
	},
	{	/* faces (numfaces + indexes into vertices) */
		/*  faces must be specified clockwise from the outside */
		4,	0, 1, 2, 3,
		4, 	7, 6, 5, 4,
		4, 	1, 0, 4, 5,
		4,	3, 2, 6, 7,
		4,	2, 1, 5, 6,
		4,	0, 3, 7, 4,
	}
},		/* leave a comma to separate from the next include file */
/* end */
