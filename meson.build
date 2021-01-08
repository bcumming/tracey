project('tracey', 'cpp',
  version: '0.1.0dev',
  license: 'BSD',
  default_options : ['cpp_std=c++17'])

version = '0.1.0dev'

tracey_inc = include_directories('include')

tracey_src = files('src/event.cpp',
                   'src/id.cpp',
                   'src/tracey.cpp',
                   'src/threads.cpp',
                   'src/clock.cpp')

fmt_dep = dependency('fmt',
                     method : 'cmake',
                     modules : ['fmt::fmt'])

thread_dep = dependency('threads')

tracey_lib = library('tracey', tracey_src,
                     include_directories: tracey_inc,
                     dependencies : [fmt_dep, thread_dep],
                     install : true)

# Install headers.
install_subdir('include/tracey', install_dir : 'include')

# Generate cmake configuration for using tracey in CMake projects.
cmake = import('cmake')
conf = configuration_data() # no additional configuration for now.
cmake.configure_package_config_file(name: 'tracey',
                                    input: 'tracey.cmake.in',
                                    configuration: conf)

# Generate pkgconfig.
pkg = import('pkgconfig')
pkg.generate(tracey_lib)
