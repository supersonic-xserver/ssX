/* $XFree86$ */


typedef struct _CacheInfo {
    int id;             /* cache id */
    int x;              /* x position in offscreen memory */
    int y;              /* y position in offscreen memory */
    int w;              /* expanded width */
    int h;              /* expanded height */
    int nx;             /* number of times expanded in x */
    int ny;             /* number of times expanded in y */
    int pix_w;          /* original pixmap width */
    int pix_h;          /* original pixmap height */
    int fg_color;       /* stipple foreground color */
    int bg_color;       /* stipple background color */
    int cache_width;    /* width of cache slot (typically 64, 128, or 256) */
    int cache_height;   /* height of cache slot (typically 64, 128, or 256) */
    int flags;          /* non zero if fixed pattern */
#if 0
    int pattern0;       /* if fixed pattern, pattern 0 register contents */
    int pattern1;       /* if fixed pattern, pattern 1 register contents */
#endif
    unsigned int lru;   /* lru counter */
} CacheInfo, *CacheInfoPtr;

#ifdef PIXPRIV
typedef struct _xf86PixPriv {
    int slot;		/* Offscreen cache slot number */
} xf86PixPrivRec, *xf86PixPrivPtr;
#endif

int xf86CacheTile(
#if NeedFunctionPrototypes
    PixmapPtr pix
#endif
);

int xf86CacheStipple(
#if NeedFunctionPrototypes
    DrawablePtr pDrawable,
    GCPtr	pGC
#endif
);
