# Prime Abstraction Layer

<img src="resources/PAL.png?raw=true" alt="PAL Logo" width=400 height=400/>

Prime Abstraction Layer is an Open Source, multi-platform abstraction library for application development. 

## Platform support
PAL supports Windows currently but Linux, Andriod and macos support will be added down the road.

### Prerequisites
- Mingw

### Prerequisites for Windows
- Make for Windows
- Git for Windows

## Getting Started
To get started, get all of the prerequisites fosr your current platform (see above). After this, clone the repository: `git clone https://github.com/nichcode/PAL.

To generate PAL and tests for windows, open command prompt in the root directory of PAL and run `premake\premake5.exe gmake2 --file=setup.lua --with-tests`

To generate PAL without tests for window, open command prompt in the root directory of PAL and run `premake\premake5.exe gmake2 --file=setup.lua`

# Building
There are two build types available, Debug and Release. Debug includes debug symbols and is optimal for development and exploration, while Release is ideal for performance.
To build PAL in debug, run `make all config=debug` at the root directory of PAL.
To build PAL in release, run `make all config=release` at the root directory of PAL.

### Supported features:
- Fast 2D rendering
- Text Rendering
- Windowing
- Opengl

### Main features to come:
- DirectX
- Vulkan
- Audio system
- Multithreading
- Circle Rendering
- Line Rendering
- Post Processing
- Custom Shaders
- 2D Physics