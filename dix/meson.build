srcs_dix = [
    'atom.c',
    'colormap.c',
    'cursor.c',
    'devices.c',
    'dispatch.c',
    'dixfonts.c',
    'dixutils.c',
    'events.c',
    'extension.c',
    'gc.c',
    'globals.c',
    'glyphcurs.c',
    'grabs.c',
    'initatoms.c',
    'main.c',
    'pixmap.c',
    'privates.c',
    'property.c',
    'resource.c',
    'swaprep.c',
    'swapreq.c',
    'tables.c',
    'window.c',
]

dix_inc = [
    include_directories('.'),          # The current 'dix' folder
    include_directories('../include'), # The root 'include' folder
    include_directories('../Xext'),    # The root 'Xext' folder
    include_directories('../programs/Xserver/include') # Crucial for 2009 header paths
]

# Build the main DIX core
libxserver_dix = static_library('libxserver_dix',
    srcs_dix,
    include_directories: [inc, dix_inc],
    dependencies: common_dep,
    c_args: ['-DSSX_LEGACY_MODE']
)

# libxserver_main provides the main() entry point for Xvfb and other servers
# This uses stubmain.c which provides a default main() that calls dix_main()
libxserver_main = static_library('libxserver_main',
    'stubmain.c',
    include_directories: [inc, dix_inc],
    dependencies: common_dep,
    c_args: ['-DSSX_LEGACY_MODE']
)
