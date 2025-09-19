cmake_minimum_required(VERSION 3.20)
project(AdventOfCode)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

option(DAY_TO_BUILD "Path to the day's .cpp file to build" "")

if(DAY_TO_BUILD)
    get_filename_component(DAY_NAME ${DAY_TO_BUILD} NAME_WE)

    get_filename_component(DAY_DIR ${DAY_TO_BUILD} DIRECTORY)

    string(REGEX MATCH "years/([0-9]+)/" _match "${DAY_DIR}")
    set(DAY_YEAR "${CMAKE_MATCH_1}")

    message(STATUS "Building day: ${DAY_NAME} from ${DAY_TO_BUILD} (year ${DAY_YEAR})")

    add_executable(${DAY_NAME} ${DAY_TO_BUILD})
    target_include_directories(${DAY_NAME} PRIVATE include)

    set_target_properties(${DAY_NAME} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${DAY_YEAR})
else()
    message(STATUS "No day specified. Please pass -DDAY_TO_BUILD=<years/1970/day01/day01.cpp>")
endif()
