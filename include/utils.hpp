#pragma once

#include <string>
#include <vector>

namespace aoc
{

std::vector<std::string> read_lines_skip_empties(const std::string &filename);

std::vector<std::string> read_lines(const std::string &filename);

std::vector<int> read_lines_as_int(const std::string &filename);

std::vector<int> read_lines_as_int_empty_as_zero(const std::string &filename);

std::vector<std::string> split(const std::string &s, char delimiter);

std::string trim(const std::string &s);
} // namespace aoc
