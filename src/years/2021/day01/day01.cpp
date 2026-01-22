// AOC
#include "utils.hpp"

// STD
#include <iostream>
#include <vector>

int solvePart1(const std::vector<int> &nums)
{
	int num_of_increasaes = 0;
	for (size_t i = 1; i < nums.size(); i++)
	{
		if (nums[i] > nums[i - 1])
		{
			num_of_increasaes++;
		}
	}
	return num_of_increasaes;
}

int solvePart2(const std::vector<int> &nums)
{
	int num_of_increases = 0;
	for (size_t i = 3; i < nums.size(); i++)
	{
		int prev_sum = nums[i - 3] + nums[i - 2] + nums[i - 1];
		int curr_sum = nums[i - 2] + nums[i - 1] + nums[i];
		if (curr_sum > prev_sum)
			num_of_increases++;
	}
	return num_of_increases;
}

int main()
{
	auto lines = aoc::readLinesAsInts("src/years/2021/day01/input/input.txt");

	// Part 1
	int num_of_increases = solvePart1(lines);
	std::cout << "Part 1: " << num_of_increases << "\n";

	// Part 2
	num_of_increases = solvePart2(lines);
	std::cout << "Part 2: " << num_of_increases << "\n";
}
