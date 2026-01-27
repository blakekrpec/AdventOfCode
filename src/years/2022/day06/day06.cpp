// AOC
#include "utils.hpp"

// STD
#include <iostream>
#include <string>
#include <unordered_set>

bool isUnique(const std::string &input)
{
	std::unordered_set<char> seen;

	for (const char c : input)
	{
		if (!seen.insert(c).second)
		{
			return false;
		}
	}
	return true;
}

int solvePart1(const std::vector<std::string> &lines)
{
	for (const std::string &line : lines)
	{
		for (size_t i = 3; i < (line.size() - 3); i++)
		{
			std::string sub_str = line.substr(i - 3, 4);

			bool is_unique = isUnique(sub_str);

			if (is_unique)
			{
				return i + 1;
			}
		}
	}
	return 0;
}

int solvePart2(const std::vector<std::string> &lines)
{
	for (const std::string &line : lines)
	{
		for (size_t i = 13; i < (line.size() - 13); i++)
		{
			std::string sub_str = line.substr(i - 13, 14);

			bool is_unique = isUnique(sub_str);

			if (is_unique)
			{
				return i + 1;
			}
		}
	}
	return 0;
}

int main()
{
	const auto lines = aoc::readLines("src/years/2022/day06/input/input.txt");

	int marker = solvePart1(lines);
	std::cout << "Part 1: " << marker << "\n";

	marker = solvePart2(lines);
	std::cout << "Part 2: " << marker << "\n";

	return 0;
}
