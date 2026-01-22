// AOC
#include "utils.hpp"

// STD
#include <cctype>
#include <iostream>
#include <string>
#include <vector>

int alphabetToInt(const char c)
{
	int value = -1;

	if (!std::isupper(c))
	{
		value = int(c) - 96;
	}
	else
	{
		value = int(c) - 38;
	}

	return value;
}

int solvePart1(const std::vector<std::string> &lines)
{
	int sum_of_priorities = 0;
	char match = ' ';

	for (const auto &line : lines)
	{
		std::string left = line.substr(0, line.length() / 2);
		std::string right = line.substr(line.length() / 2, line.length());
		for (const auto l : left)
		{
			if (right.find(l) != std::string::npos)
			{
				match = l;
				break;
			}
		}

		sum_of_priorities += alphabetToInt(match);
	}

	return sum_of_priorities;
}

int solvePart2(const std::vector<std::string> &lines)
{
	int sum_of_badge_priorities = 0;
	char match = ' ';

	for (int i = 2; i < lines.size(); i += 3)
	{
		const std::string line0 = lines[i - 2];
		const std::string line1 = lines[i - 1];
		const std::string line2 = lines[i];

		for (const char c : line0)
		{
			if (line1.find(c) != std::string::npos && line2.find(c) != std::string::npos)
			{
				match = c;
				break;
			}
		}

		sum_of_badge_priorities += alphabetToInt(match);
	}

	return sum_of_badge_priorities;
}

int main()
{
	const auto lines = aoc::readLines("src/years/2022/day03/input/input.txt");

	// Part 1
	int sum_of_priorities = solvePart1(lines);
	std::cout << "Part 1: " << sum_of_priorities << "\n";

	// Part 1
	int sum_of_badge_priorities = solvePart2(lines);
	std::cout << "Part 2: " << sum_of_badge_priorities << "\n";

	return 0;
}
