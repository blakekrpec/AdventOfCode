// AOC
#include "utils.hpp"

// STD
#include <iostream>
#include <string>

// Adds positive or negative number to a dial with num_dial_positions numbers on it. If it reaches either end
// of the dial (0, or num_dial_positions) it circles back. e.g 98, 99, 0, or 2, 1, 0, 99 for num_dial_positions = 100.
int cyclicAdd(int dial_pos, int val, int num_dial_positions)
{
	return (((dial_pos + val) % num_dial_positions) + num_dial_positions) % num_dial_positions;
}

// Counts the number of times a dial with num_dial_positions numbers, on dial position dial_pos, rotated by delta (+
// CW, - CCW) would pass zero.
int countRevolutions(int dial_pos, int delta, int num_dial_positions)
{
	if (delta == 0)
	{
		return 0;
	}

	int count = 0;

	if (delta > 0)
	{
		if (dial_pos == 0)
		{
			count = delta / num_dial_positions;
		}
		else
		{
			int dist_to_zero = num_dial_positions - dial_pos;
			if (delta >= dist_to_zero)
			{
				count = 1 + (delta - dist_to_zero) / num_dial_positions;
			}
		}
	}
	else
	{
		int abs_delta = -delta;

		if (dial_pos == 0)
		{
			count = abs_delta / num_dial_positions;
		}
		else
		{
			int dist_to_zero = dial_pos;
			if (abs_delta >= dist_to_zero)
			{
				count = 1 + (abs_delta - dist_to_zero) / num_dial_positions;
			}
		}
	}

	return count;
}

int solvePart1(const std::vector<std::string> &moves)
{
	int password = 0;
	int dial_pos = 50;
	constexpr int NUM_DIAL_POSITIONS = 100;

	for (auto &line : moves)
	{
		const char dir = line[0];
		const int amount = std::stoi(line.substr(1));
		int delta = (dir == 'L') ? -amount : amount;

		// Rotate the dial in appropriate direction (CW/CCW).
		dial_pos = cyclicAdd(dial_pos, delta, NUM_DIAL_POSITIONS);

		if (dial_pos == 0)
		{
			password++;
		}
	}

	return password;
}

int solvePart2(const std::vector<std::string> &moves)
{
	int password = 0;
	int dial_pos = 50;
	int revs = 0;
	constexpr int NUM_DIAL_POSITIONS = 100;

	for (auto &line : moves)
	{
		const char dir = line[0];
		const int amount = std::stoi(line.substr(1));
		int delta = (dir == 'L') ? -amount : amount;

		// Count how many times the upcoming rotation will pass 0 on the dial.
		password += countRevolutions(dial_pos, delta, NUM_DIAL_POSITIONS);

		// Rotate the dial in appropriate direction (CW/CCW).
		dial_pos = cyclicAdd(dial_pos, delta, NUM_DIAL_POSITIONS);
	}

	return password;
}

int main()
{
	auto lines = aoc::read_lines("src/years/2025/day01/input/input.txt");

	// Part 1
	int password = solvePart1(lines);
	std::cout << "Part 1: " << password << "\n";

	// Part 2
	int password2 = solvePart2(lines);
	std::cout << "Part 2: " << password2 << "\n";
}
