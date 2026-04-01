# Phase 1 uaegfx skeleton for ssX
#
# This is intentionally minimal. It may require adjustment to match the
# exact driver registration and build style used by ssX.

uaegfx_sources = files(
  'uaegfx_driver.c',
  'uaegfx_screen.c',
  'uaegfx_fb.c',
  'uaegfx_input.c',
)

# Example for an in-tree/static style build. Adjust to match ssX.
xorg_driver_modules += { 'uaegfx': { 'sources': uaegfx_sources } }
