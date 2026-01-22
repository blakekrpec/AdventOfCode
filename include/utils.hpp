#pragma once

#include <string>
#include <vector>

namespace aoc
{

std::vector<std::string> readLinesSkipEmpties(const std::string &filename);

std::vector<std::string> readLines(const std::string &filename);

std::vector<int> readLinesAsInts(const std::string &filename);

std::vector<int> readLinesAsIntsEmptyAsZero(const std::string &filename);

std::vector<std::string> split(const std::string &s, char delimiter);

std::string trim(const std::string &s);
} // namespace aoc
