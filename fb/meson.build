srcs_fb = [
    'fballpriv.c', 'fbarc.c', 'fbbits.c', 'fbblt.c', 'fbbltone.c',
    'fbcmap_mi.c', 'fbcopy.c', 'fbfill.c', 'fbfillrect.c', 'fbfillsp.c',
    'fbgc.c', 'fbgetsp.c', 'fbglyph.c', 'fbimage.c', 'fbline.c',
    'fboverlay.c', 'fbpict.c', 'fbpixmap.c', 'fbpoint.c', 'fbpush.c',
    'fbscreen.c', 'fbseg.c', 'fbsetsp.c', 'fbsolid.c', 'fbtrap.c',
    'fbutil.c', 'fbwindow.c',
]

hdrs_fb = [
    'fb.h', 'fboverlay.h', 'fbpict.h', 'fbrop.h', 'wfbrename.h'
]

# Internal Static Library - KEEP 'pic: true' here
# This is required because this static code will be baked into the main Xorg binary
libxserver_fb = static_library('libxserver_fb',
    srcs_fb,
    include_directories: inc,
    dependencies: common_dep,
    pic: true,
)

# Shared Library - REMOVE 'pic: true'
# shared_library is PIC by default; Meson 1.10.0 is rejecting the redundant keyword
fb_lib = shared_library('fb',
    srcs_fb,
    include_directories: inc,
    dependencies: common_dep,
    install: true,
    install_dir: join_paths(get_option('module_dir'), 'lib'),
    override_options: ['b_lundef=false']
)

wfb_args = '-DFB_ACCESS_WRAPPER'

# WFB Internal Static - KEEP 'pic: true'
libxserver_wfb = static_library('libxserver_wfb',
    srcs_fb,
    c_args: wfb_args,
    include_directories: inc,
    dependencies: common_dep,
    pic: true,
    build_by_default: false,
)

# WFB Shared Library - REMOVE 'pic: true'
wfb_lib = shared_library('wfb',
    srcs_fb,
    c_args: wfb_args,
    include_directories: inc,
    dependencies: common_dep,
    install: true,
    install_dir: join_paths(get_option('module_dir'), 'lib'),
    override_options: ['b_lundef=false']
)

install_data(hdrs_fb, install_dir: xorgsdkdir)

set_variable('fb_lib', fb_lib)
set_variable('wfb_lib', wfb_lib)
