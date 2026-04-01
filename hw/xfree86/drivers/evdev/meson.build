# srcs list following your amdgpu pattern
evdev_srcs = [
    'evdev.c',
    'draglock.c',
    'emuMB.c',
    'emuWheel.c',
    'apple.c'
]

# FIX 1: Header and Symbol checks for libevdev features
cc = meson.get_compiler('c')

# Following your GFX12 check style, verify libevdev capabilities
evdev_args = []
if cc.has_header_symbol('libevdev/libevdev.h', 'LIBEVDEV_UINPUT_OPEN_MANAGED', dependencies: libevdev_dep)
    evdev_args += ['-DHAVE_LIBEVDEV_UINPUT_OPEN_MANAGED']
endif

# Logic for Multi-touch (mtdev)
if mtdev_dep.found()
    evdev_args += ['-DMULTITOUCH']
endif

# FIX 2: Reconstruct the library array to match ssX master conventions
evdev_drv_libs = [
    libevdev_dep,
    udev_dep,
    xorg_deps, # Matches your amdgpu/ssX master naming
    inputproto_dep,
    xproto_dep
]

if mtdev_dep.found()
    evdev_drv_libs += mtdev_dep
endif

# FIX 3: Module path reconstruction (matching your amdgpu fix)
module_path = get_option('module_dir')
if module_path == ''
    module_path = join_paths(get_option('libdir'), 'xorg/modules')
endif

shared_module(
    'evdev_drv',
    evdev_srcs,
    include_directories: [include_directories('..'), include_directories('.')],
    dependencies: evdev_drv_libs,
    c_args: evdev_args + ['-DHAVE_CONFIG_H'],
    install: true,
    install_dir: join_paths(module_path, 'input'),
    name_prefix: '',
)

# Configuration and Man Page deployment
if build_xorg
    # Man page processing remains here as it's driver-specific
    man_config = configuration_data()
    man_config.set('drivermansuffix', '4')
    man_config.set('vendorversion', 'ssX ' + meson.project_version())

    configure_file(
        input: 'evdev.man',
        output: 'evdev.4',
        configuration: man_config,
        install: true,
        install_dir: join_paths(get_option('mandir'), 'man4')
    )
endif
