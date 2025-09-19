# Advent of Code – C++ Solutions

This project contains my solutions for **Advent of Code**, written in modern C++ and built with **Clang**, **CMake**, and **Ninja**.

Clone the repo

`git clone url`

Make sure you have the following installed:

- **LLVM / Clang** – https://github.com/llvm/llvm-project/releases
- **CMake** – https://cmake.org/download/
- **Ninja** – https://ninja-build.org/

Ensure `clang` and `ninja` are in your `PATH` before continuing.

To build 

`mkdir build`

`cmake -S . -B build -G Ninja "-DDAY_TO_BUILD=years/2023/day01/day01.cpp" -DCMAKE_EXPORT_COMPILE_COMMANDS=ON`

`cmake --build build`

To run

`./build/<year>/<day>` e.g. `./build/2025/day01`
