# Prime Abstraction Layer

<img src="resources/prime.png?raw=true" alt="Prime Logo" width=150 height=150/>

***
Prime is a Multi-Platform and Mulit Graphics API Abstraction Library. Currently prime supports windows platform and supports opengl graphics API fully and a little of directx11. prime dependencies are contailed in the source files.

***

## Getting Started
Visual Studio 2019  is recommended, currenty prime is tested only on windows.

Start by cloning the repository with `git clone https://github.com/nichcode/prime`.

1. If build prime with the tests, Run the [generate_test.bat](https://github.com/nichcode/prime/main/generate_test.bat) file found in the `main directory` folder. This will generate the project with the test application.

2. If build prime without the tests, Run the [generate.bat](https://github.com/nichcode/prime/main/generate.bat) file found in the `main directory` folder. This will generate the project without the test application.

## The Plan
The plan for prime is to create an abstraction layer for things like window management, threads, issuing grahics commands ie. `opengl, directx, vulkan, metal etc` without the user worrying about the platform and API they are using.

### Main features to come:
- Support for (DirectX, Vulkan, Metal)
- Audio system
- MultiThreading
- Job system
- A fast and SIMD maths library