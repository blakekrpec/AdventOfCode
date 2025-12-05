// AOC
#include "utils.hpp"

// STD
#include <iostream>

int solvePart1(const std::string &input)
{
	for (int i = 3; i < input.length(); i++)
	{
		std::string msg = input.substr(i - 3, 4);
		std::cout << msg << "\n";
	}

	return 0;
}

int main()
{
	const auto lines = aoc::read_lines("src/years/2022/day06/input/input.txt");

	std::cout << lines[0] << "\n";
	int marker = solvePart1(lines[0]);

	return 0;
}
