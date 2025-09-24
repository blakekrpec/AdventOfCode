# Advent of Code – C++ Solutions

This project contains my solutions for **Advent of Code**, written in modern C++ and built with **Clang**, **CMake**, and **Ninja**.

Clone the repo

`git clone https://github.com/blakekrpec/AdventOfCode.git`

To build 

`mkdir build`

`cmake -S . -B build -G Ninja "-DDAY_TO_BUILD=years/<year>/<day>/<day>.cpp" -DCMAKE_EXPORT_COMPILE_COMMANDS=ON` 

e.g. `cmake -S . -B build -G Ninja "-DDAY_TO_BUILD=years/2025/day01/day01.cpp" -DCMAKE_EXPORT_COMPILE_COMMANDS=ON` 

`cmake --build build`

To run

`./build/<year>/<day>`

e.g. `./build/2025/day01`

To clean

`rm build/`
