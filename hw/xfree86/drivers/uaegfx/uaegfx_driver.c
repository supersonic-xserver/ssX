#include "uaegfx.h"

#include "xf86Module.h"
#include "xf86Helper.h"
#include "xf86Priv.h"
#include "compiler.h"

#define UAEGFX_NAME "uaegfx"
#define UAEGFX_DRIVER_NAME "uaegfx"
#define UAEGFX_CHIP 0x55414746 /* 'UAGF' */

static const OptionInfoRec *UAEGFXAvailableOptions(int chipid, int busid);
static void UAEGFXIdentify(int flags);
static Bool UAEGFXProbe(DriverPtr drv, int flags);

_X_EXPORT DriverRec UAEGFX = {
    UAEGFX_VERSION_MAJOR * 1000 + UAEGFX_VERSION_MINOR,
    UAEGFX_DRIVER_NAME,
    UAEGFXIdentify,
    UAEGFXProbe,
    UAEGFXAvailableOptions,
    NULL,
    0,
    NULL,
    0
};

static XF86ModuleVersionInfo uaegfxVersRec = {
    "uaegfx",
    MODULEVENDORSTRING,
    MODINFOSTRING1,
    MODINFOSTRING2,
    XORG_VERSION_CURRENT,
    UAEGFX_VERSION_MAJOR,
    UAEGFX_VERSION_MINOR,
    UAEGFX_VERSION_PATCH,
    ABI_CLASS_VIDEODRV,
    ABI_VIDEODRV_VERSION,
    MOD_CLASS_VIDEODRV,
    {0, 0, 0, 0}
};

_X_EXPORT XF86ModuleData uaegfxModuleData = { &uaegfxVersRec, NULL, NULL };

static const OptionInfoRec *
UAEGFXAvailableOptions(int chipid, int busid)
{
    (void)chipid;
    (void)busid;
    return NULL;
}

static void
UAEGFXIdentify(int flags)
{
    (void)flags;
    xf86Msg(X_INFO, "uaegfx: phase 1 Amiga RTG pseudo-driver scaffold
");
}

static Bool
UAEGFXProbe(DriverPtr drv, int flags)
{
    int numDevSections;
    GDevPtr *devSections = NULL;
    int numUsed;
    int i;

    if (flags & PROBE_DETECT)
        return FALSE;

    numDevSections = xf86MatchDevice(UAEGFX_DRIVER_NAME, &devSections);
    if (numDevSections <= 0)
        return FALSE;

    numUsed = numDevSections;
    for (i = 0; i < numUsed; i++) {
        ScrnInfoPtr pScrn = NULL;
        int entityIndex;

        entityIndex = xf86ClaimNoSlot(drv, UAEGFX_CHIP, devSections[i], TRUE);
        if (entityIndex < 0)
            continue;

        pScrn = xf86AllocateScreen(drv, 0);
        if (pScrn == NULL)
            continue;

        xf86AddEntityToScreen(pScrn, entityIndex);

        pScrn->driverVersion = UAEGFX_VERSION_MAJOR * 1000 + UAEGFX_VERSION_MINOR;
        pScrn->driverName = UAEGFX_DRIVER_NAME;
        pScrn->name = UAEGFX_NAME;
        pScrn->Probe = UAEGFXProbe;
        pScrn->PreInit = UAEGFXPreInit;
        pScrn->ScreenInit = UAEGFXScreenInit;
        pScrn->SwitchMode = UAEGFXSwitchMode;
        pScrn->AdjustFrame = UAEGFXAdjustFrame;
        pScrn->EnterVT = UAEGFXEnterVT;
        pScrn->LeaveVT = UAEGFXLeaveVT;
        pScrn->FreeScreen = UAEGFXFreeScreen;
        pScrn->ValidMode = UAEGFXValidMode;

        xf86Msg(X_INFO, "uaegfx: allocated screen stub for entity %d
", entityIndex);
    }

    return (numUsed > 0);
}
