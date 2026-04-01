# XInput Modular Source Files
# ============================
#
# This is the new modular architecture for the XInput extension.
# Original individual source files have been migrated into the following modules:
#
# xinput_v1.c: XInput 1.x protocol implementation
# xinput_v2.c: XInput 2.x protocol implementation  
# xinput_shared.h: Common macros and helper declarations
# extinit.c: Extension initialization and dispatch
#
# Migration Status: Phase 2 - Modular sources active
# Migration Credits: azuriteshift, collinbeyer

# Modular XInput sources (NEW - Phase 2)
srcs_xi = [
    'xinput_v1.c',
    'xinput_v2.c',
    'extinit.c',
]

libxserver_xi = static_library('libxserver_xi',
    srcs_xi,
    include_directories: inc,
    dependencies: common_dep,
)

srcs_xi_stubs = ['stubs.c']
libxserver_xi_stubs = static_library('libxserver_xi_stubs',
    srcs_xi_stubs,
    include_directories: inc,
    dependencies: common_dep,
)
