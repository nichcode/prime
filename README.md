# Prime Abstraction Layer

<img src="resources/prime.png?raw=true" alt="prime Logo" width=400 height=400/>

Prime is an Open Source, multi-platform abstraction library for application development. 

## Platform support
Primeonly supports Windows currently but Linux, Andriod and macos support will be added down the road.

### Prerequisites
- Mingw

### Prerequisites for Windows
- Make for Windows
- Git for Windows

## Getting Started
To get started, get all of the prerequisites fosr your current platform (see above). After this, clone the repository: `git clone https://github.com/nichcode/prime.

To generate prime and prime tests for windows, open command prompt in the root directory of prime and run `premake\premake5.exe gmake2 --file=setup.lua --with-tests`

To generate prime without prime tests for window, open command prompt in the root directory of prime and run `premake\premake5.exe gmake2 --file=setup.lua`

# Building
There are two build types available, Debug and Release. Debug includes debug symbols and is optimal for development and exploration, while Release is ideal for performance.
To build prime in debug, run `make all config=debug` at the root directory of prime.
To build prime in release, run `make all config=release` at the root directory of prime.

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
- 2D Physics