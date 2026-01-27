
// AOC
#include "utils.hpp"

// STD
#include <iostream>
#include <string>

long long getMaxIntFromString(const std::string &str, int digits)
{
	if (digits > str.length())
	{
		std::cout << "Number of digits requested is > string length."
				  << "\n";
		return 0;
	}
	if (digits == str.length())
	{
		return std::stoi(str);
	}

	int max{0};			// storage for searching for max digits
	int prev_index{-1}; // -1 since our logic needs to set i = prev_index+1 and we want it to start at 0

	std::string result{};

	// Loop over the number of digits we need to find
	for (size_t k = 0; k < digits; k++)
	{
		max = 0;
		// Iter over portion of the string still available for searching for kth digit
		for (size_t i = prev_index + 1; i <= ((str.length() - 1) - ((digits - 1) - k)); i++)
		{
			int c = str[i] - '0'; // Convert char to int
			if (c > max)
			{
				max = c;
				prev_index = i;
			}
		}
		result += std::to_string(max);
	}
	return std::stoll(result);
}

long long solve(const std::vector<std::string> &lines, int digits)
{
	long long sum_joltage{0};

	for (const auto &line : lines)
	{
		sum_joltage += getMaxIntFromString(line, digits);
	}

	return sum_joltage;
}

int main()
{
	auto lines = aoc::readLines("src/years/2025/day03/input/input.txt");

	// Part 1
	long long result = solve(lines, 2);
	std::cout << "Part 1: " << result << "\n";

	// Part 2
	long long result2 = solve(lines, 12);
	std::cout << "Part 2: " << result2 << "\n";
}
