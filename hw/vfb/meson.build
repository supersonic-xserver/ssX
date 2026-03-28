srcs = [
    'InitInput.c',
    'InitOutput.c',
    '../../mi/miinitext.c',
]

# Build link_with list conditionally - some libs may be empty arrays or static_library objects in legacy mode
vfb_link_with = [
    libxserver_main,    # The stubmain.c entry point
    libxserver_os,      # OS/Logging/Timers
]

# Only add GLX if it was built (not empty array)
# libxserver_glx can be either [] (empty array) or a static_library object
if build_glx
    vfb_link_with += libxserver_glx
endif


# Only add XKB stubs if they exist - check if it's not an empty array
# libxserver_xkb_stubs is a static_library, always add it
vfb_link_with += libxserver_xkb_stubs

# Only add XI stubs if they exist - check if it's not an empty array
# libxserver_xi_stubs is a static_library, always add it
vfb_link_with += libxserver_xi_stubs

xvfb_server = executable(
    'Xvfb',
    ['InitInput.c', 'InitOutput.c'],
    include_directories: inc,
    dependencies: [common_dep],
    link_whole: [
        libxserver,         # DIX (The 2009 Restoration Core)
        libxserver_fb,      # Framebuffer
        libxserver_mi,      # Machine Independent Layer
    ],
    link_with: vfb_link_with,
    install: true,
)

install_man(configure_file(
    input: 'man/Xvfb.man',
    output: 'Xvfb.1',
    configuration: manpage_config,
))
