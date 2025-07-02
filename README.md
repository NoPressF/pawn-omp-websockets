## Required Tools

* [CMake 3.19+](https://cmake.org/)
* [Conan 1.53+](https://conan.io/)
* [Visual Studio 2019+](https://www.visualstudio.com/) (on Windows)
* [Boost 1.86.0](https://www.boost.org/releases/1.86.0/)
* Clang (on Linux)

Visual Studio needs the `Desktop development with C++` workload with the `MSVC v142`, `Windows 10 SDK`, and `C++ Clang tools for Windows` components.

## Sources

```bash
# With HTTPS:
git clone --recursive https://github.com/NoPressF/pawn-omp-websockets
# With SSH:
git clone --recursive git@github.com:NoPressF/pawn-omp-websockets
```

## Building on Windows

```
mkdir build
cd build
cmake .. -A Win32 -T ClangCL
cmake --build . --config RelWithDebInfo
```

Open Visual Studio and build the solution.

## Building on Linux

```bash
mkdir build
cd build
# May need to configure this line.
export CC=/usr/lib/llvm/13/bin/clang CXX=/usr/lib/llvm/13/bin/clang++
cmake .. -G Ninja -DCMAKE_C_FLAGS=-m32 -DCMAKE_CXX_FLAGS=-m32 -DCMAKE_BUILD_TYPE=Debug \
cmake --build . --config Debug
```
