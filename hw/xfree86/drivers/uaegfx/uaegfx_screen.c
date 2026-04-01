#include "uaegfx.h"

#include <stdlib.h>
#include <string.h>

#include "fb.h"
#include "xf86Helper.h"
#include "xf86fbman.h"

static Bool UAEGFXSetDefaults(ScrnInfoPtr pScrn, UaegfxScreenState *st);

UaegfxScreenState *
UAEGFXGetState(ScrnInfoPtr pScrn)
{
    return (UaegfxScreenState *)pScrn->driverPrivate;
}

UaegfxScreenState *
UAEGFXAllocState(ScrnInfoPtr pScrn)
{
    UaegfxScreenState *st;

    st = calloc(1, sizeof(*st));
    if (st == NULL) {
        xf86DrvMsg(pScrn->scrnIndex, X_ERROR,
                   "uaegfx: failed to allocate driver state
");
        return NULL;
    }

    pScrn->driverPrivate = st;
    st->pScrn = pScrn;
    return st;
}

void
UAEGFXFreeState(ScrnInfoPtr pScrn)
{
    UaegfxScreenState *st = UAEGFXGetState(pScrn);
    if (st == NULL)
        return;

    free(st->source_pixels);
    free(st);
    pScrn->driverPrivate = NULL;
}

static Bool
UAEGFXSetDefaults(ScrnInfoPtr pScrn, UaegfxScreenState *st)
{
    (void)pScrn;

    st->width = 1280;
    st->height = 720;
    st->bits_per_pixel = 32;
    st->depth = 24;
    st->stride = st->width * 4;
    st->use_shadow = FALSE;
    st->use_xaa = FALSE;

    return TRUE;
}

Bool
UAEGFXPreInit(ScrnInfoPtr pScrn, int flags)
{
    UaegfxScreenState *st;

    if (flags & PROBE_DETECT)
        return FALSE;

    if (pScrn->numEntities != 1)
        return FALSE;

    if (pScrn->monitor == NULL)
        return FALSE;

    st = UAEGFXAllocState(pScrn);
    if (st == NULL)
        return FALSE;

    if (!UAEGFXSetDefaults(pScrn, st))
        return FALSE;

    pScrn->chipset = UAEGFX_NAME;
    pScrn->videoRam = (st->stride * st->height) / 1024;
    pScrn->bitsPerPixel = st->bits_per_pixel;
    pScrn->depth = st->depth;
    pScrn->virtualX = st->width;
    pScrn->virtualY = st->height;
    pScrn->displayWidth = st->width;
    pScrn->rgbBits = 8;

    pScrn->offset.red = 16;
    pScrn->offset.green = 8;
    pScrn->offset.blue = 0;
    pScrn->mask.red = 0x00ff0000;
    pScrn->mask.green = 0x0000ff00;
    pScrn->mask.blue = 0x000000ff;

    xf86DrvMsg(pScrn->scrnIndex, X_INFO,
               "uaegfx: PreInit width=%u height=%u stride=%u bpp=%u depth=%u
",
               st->width, st->height, st->stride,
               st->bits_per_pixel, st->depth);

    if (!UAEGFXGenerateTestPattern(pScrn))
        return FALSE;

    return TRUE;
}

Bool
UAEGFXScreenInit(SCREEN_INIT_ARGS_DECL)
{
    ScrnInfoPtr pScrn = xf86ScreenToScrn(pScreen);
    UaegfxScreenState *st = UAEGFXGetState(pScrn);
    VisualPtr visual;
    Bool ret;

    if (st == NULL) {
        xf86DrvMsg(pScrn->scrnIndex, X_ERROR,
                   "uaegfx: missing driver state in ScreenInit
");
        return FALSE;
    }

    st->pScreen = pScreen;

    if (!miSetPixmapDepths())
        return FALSE;

    ret = fbScreenInit(pScreen,
                       st->source_pixels,
                       pScrn->virtualX,
                       pScrn->virtualY,
                       pScrn->xDpi,
                       pScrn->yDpi,
                       pScrn->displayWidth,
                       pScrn->bitsPerPixel);
    if (!ret)
        return FALSE;

    if (pScrn->depth > 8) {
        visual = pScreen->visuals + pScreen->numVisuals;
        while (--visual >= pScreen->visuals) {
            if ((visual->class | DynamicClass) == DirectColor) {
                visual->offsetRed = pScrn->offset.red;
                visual->offsetGreen = pScrn->offset.green;
                visual->offsetBlue = pScrn->offset.blue;
                visual->redMask = pScrn->mask.red;
                visual->greenMask = pScrn->mask.green;
                visual->blueMask = pScrn->mask.blue;
            }
        }
    }

    fbPictureInit(pScreen, 0, 0);
    xf86SetBlackWhitePixels(pScreen);

    {
        BoxRec AvailFBArea;
        int lines = pScrn->videoRam * 1024 /
                    (pScrn->displayWidth * (pScrn->bitsPerPixel >> 3));

        AvailFBArea.x1 = 0;
        AvailFBArea.y1 = 0;
        AvailFBArea.x2 = pScrn->displayWidth;
        AvailFBArea.y2 = lines;
        xf86InitFBManager(pScreen, &AvailFBArea);
    }

    miInitializeBackingStore(pScreen);
    xf86SetBackingStore(pScreen);
    xf86SetSilkenMouse(pScreen);
    miDCInitialize(pScreen, xf86GetPointerScreenFuncs());

    if (!miCreateDefColormap(pScreen))
        return FALSE;

    if (!xf86HandleColormaps(pScreen, 256, pScrn->rgbBits,
                             NULL, NULL, CMAP_PALETTED_TRUECOLOR))
        return FALSE;

    st->CloseScreen = pScreen->CloseScreen;
    pScreen->CloseScreen = UAEGFXCloseScreen;
    st->screen_initialized = TRUE;
    st->fb_attached = TRUE;

    xf86DrvMsg(pScrn->scrnIndex, X_INFO,
               "uaegfx: ScreenInit completed (dummy-style framebuffer path)
");
    return TRUE;
}

Bool
UAEGFXCloseScreen(CLOSE_SCREEN_ARGS_DECL)
{
    ScrnInfoPtr pScrn = xf86ScreenToScrn(pScreen);
    UaegfxScreenState *st = UAEGFXGetState(pScrn);
    Bool ret = TRUE;

    if (st != NULL) {
        UAEGFXShutdownInput(pScreen);
        pScrn->vtSema = FALSE;
        pScreen->CloseScreen = st->CloseScreen;
        if (pScreen->CloseScreen != NULL)
            ret = (*pScreen->CloseScreen)(CLOSE_SCREEN_ARGS);
        st->screen_initialized = FALSE;
    }

    UAEGFXFreeState(pScrn);
    return ret;
}

Bool
UAEGFXSwitchMode(SWITCH_MODE_ARGS_DECL)
{
    (void)arg;
    (void)mode;
    return TRUE;
}

void
UAEGFXAdjustFrame(ADJUST_FRAME_ARGS_DECL)
{
    (void)arg;
    (void)x;
    (void)y;
}

Bool
UAEGFXEnterVT(VT_FUNC_ARGS_DECL)
{
    (void)arg;
    return TRUE;
}

void
UAEGFXLeaveVT(VT_FUNC_ARGS_DECL)
{
    (void)arg;
}

void
UAEGFXFreeScreen(FREE_SCREEN_ARGS_DECL)
{
    ScrnInfoPtr pScrn = arg;
    UAEGFXFreeState(pScrn);
}

ModeStatus
UAEGFXValidMode(SCRN_ARG_TYPE arg, DisplayModePtr mode, Bool verbose, int flags)
{
    (void)arg;
    (void)mode;
    (void)verbose;
    (void)flags;
    return MODE_OK;
}
