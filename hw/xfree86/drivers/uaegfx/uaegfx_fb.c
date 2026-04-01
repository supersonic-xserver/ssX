#include "uaegfx.h"

#include <stdlib.h>
#include <string.h>

Bool
UAEGFXAttachFramebuffer(ScrnInfoPtr pScrn, void *pixels, size_t size_bytes,
                        uint32_t stride)
{
    UaegfxScreenState *st = UAEGFXGetState(pScrn);

    if (st == NULL || pixels == NULL || size_bytes == 0 || stride == 0) {
        xf86DrvMsg(pScrn ? pScrn->scrnIndex : -1, X_ERROR,
                   "uaegfx: invalid framebuffer attachment
");
        return FALSE;
    }

    st->source_pixels = pixels;
    st->source_size = size_bytes;
    st->stride = stride;
    st->fb_attached = TRUE;
    return TRUE;
}

Bool
UAEGFXGenerateTestPattern(ScrnInfoPtr pScrn)
{
    UaegfxScreenState *st = UAEGFXGetState(pScrn);
    uint8_t *p;
    uint32_t x, y;
    size_t size;

    if (st == NULL)
        return FALSE;

    size = (size_t)st->stride * (size_t)st->height;
    st->source_pixels = calloc(1, size);
    if (st->source_pixels == NULL) {
        xf86DrvMsg(pScrn->scrnIndex, X_ERROR,
                   "uaegfx: failed to allocate source framebuffer
");
        return FALSE;
    }
    st->source_size = size;

    p = (uint8_t *)st->source_pixels;
    for (y = 0; y < st->height; ++y) {
        for (x = 0; x < st->width; ++x) {
            size_t off = (size_t)y * st->stride + (size_t)x * 4;
            p[off + 0] = 0x40;
            p[off + 1] = (uint8_t)((y * 255U) / st->height);
            p[off + 2] = (uint8_t)((x * 255U) / st->width);
            p[off + 3] = 0x00;
        }
    }

    xf86DrvMsg(pScrn->scrnIndex, X_INFO,
               "uaegfx: generated static test pattern framebuffer
");
    return TRUE;
}

Bool
UAEGFXRefreshFull(ScreenPtr pScreen)
{
    ScrnInfoPtr pScrn = xf86ScreenToScrn(pScreen);
    UaegfxScreenState *st = UAEGFXGetState(pScrn);

    if (st == NULL || !st->fb_attached || st->source_pixels == NULL) {
        xf86DrvMsg(pScrn->scrnIndex, X_ERROR,
                   "uaegfx: full refresh called without framebuffer
");
        return FALSE;
    }

    xf86DrvMsg(pScrn->scrnIndex, X_INFO,
               "uaegfx: full refresh stub invoked
");
    return TRUE;
}

Bool
UAEGFXRefreshRegions(ScreenPtr pScreen, const BoxPtr boxes, int nbox)
{
    ScrnInfoPtr pScrn = xf86ScreenToScrn(pScreen);
    UaegfxScreenState *st = UAEGFXGetState(pScrn);

    if (st == NULL || boxes == NULL || nbox < 0) {
        xf86DrvMsg(pScrn ? pScrn->scrnIndex : -1, X_ERROR,
                   "uaegfx: invalid region refresh request
");
        return FALSE;
    }

    xf86DrvMsg(pScrn->scrnIndex, X_INFO,
               "uaegfx: region refresh stub invoked (%d boxes)
", nbox);
    return TRUE;
}
