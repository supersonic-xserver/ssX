#ifndef UAEGFX_H
#define UAEGFX_H

#include <stddef.h>
#include <stdint.h>

#include "xf86.h"
#include "xf86_OSproc.h"
#include "xf86Crtc.h"
#include "xf86Str.h"
#include "xf86Priv.h"
#include "mipointer.h"
#include "micmap.h"

#ifndef UAEGFX_VERSION_MAJOR
#define UAEGFX_VERSION_MAJOR 0
#endif
#ifndef UAEGFX_VERSION_MINOR
#define UAEGFX_VERSION_MINOR 1
#endif
#ifndef UAEGFX_VERSION_PATCH
#define UAEGFX_VERSION_PATCH 0
#endif

typedef struct UaegfxScreenState {
    ScrnInfoPtr pScrn;
    ScreenPtr pScreen;

    uint32_t width;
    uint32_t height;
    uint32_t stride;
    uint32_t bits_per_pixel;
    uint32_t depth;

    void *source_pixels;
    size_t source_size;

    Bool screen_initialized;
    Bool fb_attached;
    Bool use_shadow;
    Bool use_xaa;

    CloseScreenProcPtr CloseScreen;
    void *input_userdata;
} UaegfxScreenState;

Bool UAEGFXPreInit(ScrnInfoPtr pScrn, int flags);
Bool UAEGFXScreenInit(SCREEN_INIT_ARGS_DECL);
Bool UAEGFXCloseScreen(CLOSE_SCREEN_ARGS_DECL);

Bool UAEGFXSwitchMode(SWITCH_MODE_ARGS_DECL);
void UAEGFXAdjustFrame(ADJUST_FRAME_ARGS_DECL);
Bool UAEGFXEnterVT(VT_FUNC_ARGS_DECL);
void UAEGFXLeaveVT(VT_FUNC_ARGS_DECL);
void UAEGFXFreeScreen(FREE_SCREEN_ARGS_DECL);
ModeStatus UAEGFXValidMode(SCRN_ARG_TYPE arg, DisplayModePtr mode,
                           Bool verbose, int flags);

UaegfxScreenState *UAEGFXGetState(ScrnInfoPtr pScrn);
UaegfxScreenState *UAEGFXAllocState(ScrnInfoPtr pScrn);
void UAEGFXFreeState(ScrnInfoPtr pScrn);

Bool UAEGFXAttachFramebuffer(ScrnInfoPtr pScrn, void *pixels, size_t size_bytes,
                             uint32_t stride);
Bool UAEGFXGenerateTestPattern(ScrnInfoPtr pScrn);
Bool UAEGFXRefreshFull(ScreenPtr pScreen);
Bool UAEGFXRefreshRegions(ScreenPtr pScreen, const BoxPtr boxes, int nbox);

Bool UAEGFXInitInput(ScreenPtr pScreen);
void UAEGFXShutdownInput(ScreenPtr pScreen);

#endif
