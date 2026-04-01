# uaegfx next steps inside ssX

1. Compare this skeleton against:
   - `hw/xfree86/drivers/dummy/`
   - `hw/xfree86/drivers/fbdev/`

2. Adjust the registration model:
   - static built-in
   - or classic XFree86 module registration

3. Replace stub lifecycle bodies with the exact `ssX` helper flow:
   - `PreInit`
   - `ScreenInit`
   - `CloseScreen`

4. Choose the first visible path:
   - direct framebuffer copy
   - or `shadowfb`-assisted refresh

5. Hard-code one safe mode for phase 1:
   - width
   - height
   - stride
   - `XRGB8888`

6. Wire in a generated test pattern first.
   Do not start with emulator integration.

7. After static image works:
   - add dirty rectangles
   - add focus and input callback bridge
   - add XAA fill
   - add same-screen blit
