srcs_dix = [
    'atom.c',
    'colormap.c',
    'cursor.c',
    'devices.c',
    'dispatch.c',
    'dixfonts.c',
    'main.c',
    'dixutils.c',
    'enterleave.c',
    'events.c',
    'eventconvert.c',
    'extension.c',
    'gc.c',
    'getevents.c',
    'globals.c',
    'glyphcurs.c',
    'grabs.c',
    'initatoms.c',
    'inpututils.c',
    'pixmap.c',
    'privates.c',
    'property.c',
    'ptrveloc.c',
    'region.c',
    'registry.c',
    'resource.c',
    'selection.c',
    'ssx_shims.c',
    'swaprep.c',
    'swapreq.c',
    'tables.c',
    'touch.c',
    'window.c',
]

dix_inc = [
    include_directories('.'),          # The current 'dix' folder
    include_directories('../include'), # The root 'include' folder
    include_directories('../Xext')    # The root 'Xext' folder
]

libxserver_dix = static_library('libxserver_dix',
    srcs_dix,
    include_directories: [inc, dix_inc],
    dependencies: common_dep,
)

libxserver_main = static_library('libxserver_main',
    'stubmain.c',
    include_directories: [inc, dix_inc],
    dependencies: common_dep,
)

install_data(
    'protocol.txt',
    install_dir: serverconfigdir,
)

