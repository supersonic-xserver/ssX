# Build notes

This revision is the closest compile-oriented scaffold I can produce without
actually building against the real ssX tree.

## Changes made to reduce first-build friction

- probe path now follows the dummy-driver pattern more closely
- lifecycle hooks now include:
  - PreInit
  - ScreenInit
  - SwitchMode
  - AdjustFrame
  - EnterVT
  - LeaveVT
  - FreeScreen
  - ValidMode
- ScreenInit now follows the dummy framebuffer sequence:
  - miSetPixmapDepths()
  - fbScreenInit(...)
  - RGB visual fix-up
  - fbPictureInit(...)
  - xf86SetBlackWhitePixels(...)
  - xf86InitFBManager(...)
  - miInitializeBackingStore(...)
  - xf86SetBackingStore(...)
  - xf86SetSilkenMouse(...)
  - miDCInitialize(...)
  - miCreateDefColormap(...)
  - xf86HandleColormaps(...)
  - wrap CloseScreen
- CloseScreen now restores the wrapped hook before chaining

## Honest limitation

I have not compiled this against the live ssX source tree in this environment,
so I cannot honestly guarantee a first-try build. This should be materially
closer than the previous scaffold, but there may still be minor symbol,
include-name, or build-system adjustments required.
