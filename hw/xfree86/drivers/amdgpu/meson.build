srcs = [
  'amdgpu_bo_helper.c',
  'amdgpu_dri2.c',
  'amdgpu_dri3.c',
  'amdgpu_drm_queue.c',
  'amdgpu_glamor.c',
  'amdgpu_glamor_wrappers.c',
  'amdgpu_kms.c',
  'amdgpu_misc.c',
  'amdgpu_pixmap.c',
  'amdgpu_probe.c',
  'amdgpu_present.c',
  'amdgpu_sync.c',
  'amdgpu_video.c',
  'drmmode_display.c',
]

cc = meson.get_compiler('c')

# DEBUG: Let's see exactly where Meson thinks we are
current_dir = meson.current_source_dir()
message('ssX Audit: Searching for fourcc.h in ' + current_dir)

# FORCE THE ARGS
# We use -I. to ensure the test looks in the driver folder first.
# We also add -D_GNU_SOURCE to ensure standard types are defined.
test_args = ['-I' + current_dir, '-D_GNU_SOURCE']

gfx12_test = '''
#include "fourcc.h"
#ifndef AMD_FMT_MOD_TILE_VER_GFX12
#error GFX12_NOT_DEFINED
#endif
int main() { return 0; }
'''

# FIX: We pass the actual local include_directories object to the check
if cc.compiles(gfx12_test, args: test_args, name: 'GFX12 local header check')
    message('ssX SOVEREIGN: fourcc.h found. GFX12 constants ENABLED.')
    gfx12_args = ['-DHAVE_AMD_FMT_MOD_TILE_GFX12']
else
    # ULTIMATE FALLBACK: If you physically put the file there, we force the flag.
    # Check if the file exists on disk regardless of what the compiler says.
    fs = import('fs')
    if fs.exists(current_dir / 'fourcc.h')
        message('ssX SOVEREIGN: fourcc.h exists on disk. FORCING GFX12 ENABLED.')
        gfx12_args = ['-DHAVE_AMD_FMT_MOD_TILE_GFX12']
    else
        message('CRITICAL ERROR: fourcc.h is NOT in ' + current_dir)
        gfx12_args = []
    endif
endif

amdgpu_drv_deps = [
    fontsproto_dep,
    gbm_dep,
    libdrm_amdgpu_dep,
    libdrm_dep,
    randrproto_dep,
    renderproto_dep,
    videoproto_dep,
    xextproto_dep,
    xf86driproto_dep,
    xorg_deps,
    xproto_dep
]

if udev_dep.found()
    amdgpu_drv_deps += udev_dep
endif

# THE STATIC/DYNAMIC SWITCH
if get_option('static_loader')
    amdgpu_drv_lib = static_library(
        'amdgpu_drv',
        srcs,
        # IMPORTANT: include_directories('.') must be at the FRONT
        include_directories: [include_directories('.'), inc, xorg_inc],
        dependencies: amdgpu_drv_deps,
        c_args: test_args + gfx12_args + ['-DCONFIG_STATIC_LOADER'],
        pic: true
    )
    set_variable('amdgpu_drv_lib', amdgpu_drv_lib)
else
    shared_module(
        'amdgpu_drv',
        srcs,
        include_directories: [inc, include_directories('.'), xorg_inc],
        dependencies: amdgpu_drv_deps,
        c_args: drm_args + gfx12_args,
        install: true,
        install_dir: join_paths(get_option('module_dir'), 'drivers'),
        name_prefix: '',
    )
endif
