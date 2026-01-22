// AOC
#include "utils.hpp"

// STD
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

int solvePart1(const std::vector<int> &cals)
{
	std::vector<int> elf_cals;
	int max_cals = 0;

	int current_count = 0;
	for (const auto &cal : cals)
	{
		if (cal != 0)
		{
			current_count += cal;
		}
		else
		{
			elf_cals.push_back(current_count);
			current_count = 0;
		}
	}

	auto max_itr = std::max_element(elf_cals.begin(), elf_cals.end());

	if (max_itr != elf_cals.end())
	{
		return *max_itr;
	}

	return NULL;
}

int solvePart2(const std::vector<int> &cals)
{
	std::vector<int> elf_cals;
	int top3_max_cals_sum = 0;

	int current_count = 0;
	for (const auto &cal : cals)
	{
		if (cal != 0)
		{
			current_count += cal;
		}
		else
		{
			elf_cals.push_back(current_count);
			current_count = 0;
		}
	}

	std::partial_sort(elf_cals.begin(), elf_cals.begin() + 3, elf_cals.end(), std::greater<>());

	for (size_t i = 0; i < 3; i++)
	{
		top3_max_cals_sum += elf_cals[i];
	}

	return top3_max_cals_sum;
}

int main()
{
	auto lines = aoc::readLinesAsIntsEmptyAsZero("src/years/2022/day01/input/input.txt");

	// Part 1
	int max_cal = solvePart1(lines);
	std::cout << "Part 1: " << max_cal << "\n";

	// Part 2
	int sum_of_top3_max_cal = solvePart2(lines);
	std::cout << "Part 2: " << sum_of_top3_max_cal << "\n";
}
