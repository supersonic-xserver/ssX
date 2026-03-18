/* $XFree86$ */


/*
 * This set of functions can be used by:
 *
 * ARK driver:		LSB-first, DWORD-padding
 * C&T driver:		MSB-first, DWORD-padding
 * Cirrus driver:	MSB-first, byte-padding/DWORD-padding
 * Matrox driver:       LSB-first, DWORD-padding
 */


/* Bitmap functions. */

unsigned int *xf86DrawBitmapScanline(
#if NeedFunctionPrototypes
    unsigned int *base,
    unsigned int *src,
    int nbytes
#endif
    );

unsigned int *xf86DrawBitmapScanlineMSBFirst(
#if NeedFunctionPrototypes
    unsigned int *base,
    unsigned int *src,
    int nbytes
#endif
    );

unsigned int *xf86DrawBitmapScanline3(
#if NeedFunctionPrototypes
    unsigned int *base,
    unsigned int *src,
    int npixels
#endif
    );

unsigned int *xf86DrawBitmapScanline3MSBFirst(
#if NeedFunctionPrototypes
    unsigned int *base,
    unsigned int *src,
    int npixels
#endif
    );


/*
 * These functions write a scanline of bitmap data generated from a
 * text string to the screen using color-expansion hardware. The scanline
 * is padded to a DWORD boundary.
 *
 * They can be used in different ways, for example CPU-assisted color
 * expansion to video memory, or set up of bitmap data in video memory
 * for a subsequent video-to-video memory color expansion operation,
 * or even set up for bitmap/font caching.
 */

/*
 * Write a scanline of bitmap data of _nglyph_ glyhps at address _base_
 * with an array of pointers to the glyph bitmaps (which have glyph
 * scanlines padded to a DWORD boundary) _glyphp_, line offset within
 * glyph _line_, and glyphs of width _glyphwidth_.
 * The return value points to the address just beyond the last word
 * written (return_value - _base_ = number of bytes/words written).
 */

unsigned int *xf86DrawTextScanline(
#if NeedFunctionPrototypes
    unsigned int *base,
    unsigned int **glyphp,
    int line,
    int nglyph,
    int glyphwidth
#endif
    );

/*
 * This function is for devices that want the bit order within a byte
 * to be MSBFirst (most significant bit is leftmost on the screen).
 * If the chip can do it the other way, use that.
 */

unsigned int *xf86DrawTextScanlineMSBFirst(
#if NeedFunctionPrototypes
    unsigned int *base,
    unsigned int **glyphp,
    int line,
    int nglyph,
    int glyphwidth
#endif
    );


/*
 * This structure passes addititional information for non-terminal
 * emulator fonts (different character sizes).
 */

typedef struct {
	unsigned int *bitsp;
	int width;
	int firstline;
	int lastline;
} NonTEGlyphInfo;

/*
 * This function is for proportional (non-terminal) fonts. _glyphinfop_
 * is an array of character information, including the bitmap data
 * _bitsp_, the character width _width_, the offset of the first
 * defined glyph bitmap scanline _firstline_, and the offset of the
 * last defined glyph bitmap scanline _lastline_.
 */

unsigned int *xf86DrawNonTETextScanline(
#if NeedFunctionPrototypes
    unsigned int *base,
    NonTEGlyphInfo *glyphinfop,
    int line,
    int nglyph
#endif
    );

/*
 * This is the MSB-first version of the above function.
 */

unsigned int *xf86DrawNonTETextScanlineMSBFirst(
#if NeedFunctionPrototypes
    unsigned int *base,
    NonTEGlyphInfo *glyphinfop,
    int line,
    int nglyph
#endif
    );

/*
 * This function is for color expansion for 24bpp pixels with the
 * chip in 8bpp mode, usable when the red, green and blue values
 * of the colors are equal (grayscale).
 */

unsigned int *xf86DrawTextScanline3(
#if NeedFunctionPrototypes
    unsigned int *base,
    unsigned int **glyphp,
    int line,
    int nglyph,
    int glyphwidth
#endif
    );

/*
 * This 24bpp-in-8bpp-mode function is for devices that want the bit order
 * within a byte to be MSBFirst (most significant bit is leftmost on the
 * screen).
 */

unsigned int *xf86DrawTextScanline3MSBFirst(
#if NeedFunctionPrototypes
    unsigned int *base,
    unsigned int **glyphp,
    int line,
    int nglyph,
    int glyphwidth
#endif
    );


/*
 * The following structure is the return type of yet another version
 * of some functions that allows byte-padding of scanlines.
 * The 2 low order bits of the returned _base_ indicate how many bytes have
 * been processed in last DWORD, and _bits_ holds the data. The last DWORD
 * has not been written yet.
 */

typedef struct {
	unsigned int *base;
	unsigned int bits;
} ScanlineReturn;

/*
 * This function allows byte-padding of scanlines. The 2 lower order bits
 * of base indicate how much bytes are left from the last scanline, and
 * bits contains the data for these bytes. It returns the structure
 * described above. There is only a MSB-first version (following the
 * assumption that devices that need byte-padding also use MSB-first
 * bit order).
 */

ScanlineReturn xf86DrawBitmapScanlineMSBFirstBytePadded(
#if NeedFunctionPrototypes
    unsigned int *base,
    unsigned int *src,
    unsigned int bits,
    int nbytes
#endif
    );
