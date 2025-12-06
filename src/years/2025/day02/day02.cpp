// AOC
#include "utils.hpp"

// STD
#include <iostream>
#include <string>

// Checks id consists of two identical halves (e.g. 55, 123123, 65676567).
bool isValidIDPt1(const std::string &id)
{
	if (id.length() % 2 != 0)
	{
		return true;
	}
	const std::string left = id.substr(0, id.length() / 2);
	const std::string right = id.substr(id.length() / 2);

	if (left == right)
	{
		return false;
	}

	return true;
}

// Checks id consists of series of repeating segments (e.g. 55, 565656, 1234123412341234).
bool isValidIDPt2(const std::string &id)
{
	const size_t len = id.length();

	// All the possible sliding window sizes.
	for (size_t window_size = 1; window_size <= len / 2; window_size++)
	{
		if (len % window_size != 0)
		{
			continue;
		}

		// Build what would be the repeated string if it repeats the segment at 0->window_size of id.
		const std::string pattern = id.substr(0, window_size);
		std::string repeated = "";
		for (size_t i = 0; i < len / window_size; i++)
		{
			repeated += pattern;
		}

		// If the generated repeated string matches id then id is invalid.
		if (repeated == id)
		{
			return false;
		}
	}
	return true;
}

long long solvePart1(const std::vector<std::string> &lines)
{
	long long sum_invalid_ids = 0;

	const std::string &line = lines[0];
	const std::vector<std::string> ranges = aoc::split(line, ',');

	for (const auto &range : ranges)
	{
		const size_t hyphen_pos = range.find('-');
		const std::string start_string = range.substr(0, hyphen_pos);
		const std::string end_string = range.substr(hyphen_pos + 1);

		const long long start = std::stoll(start_string);

		const long long end = std::stoll(end_string);

		for (long long i = start; i <= end; i++)
		{
			const bool valid = isValidIDPt1(std::to_string(i));
			if (!valid)
			{
				sum_invalid_ids += i;
			}
		}
	}

	return sum_invalid_ids;
}

long long solvePart2(const std::vector<std::string> &lines)
{
	long long sum_invalid_ids = 0;

	const std::string &line = lines[0];
	const std::vector<std::string> ranges = aoc::split(line, ',');

	for (const auto &range : ranges)
	{
		const size_t hyphen_pos = range.find('-');
		const std::string start_string = range.substr(0, hyphen_pos);
		const std::string end_string = range.substr(hyphen_pos + 1);

		const long long start = std::stoll(start_string);

		const long long end = std::stoll(end_string);

		for (long long i = start; i <= end; i++)
		{
			const bool valid = isValidIDPt2(std::to_string(i));
			if (!valid)
			{
				sum_invalid_ids += i;
			}
		}
	}

	return sum_invalid_ids;
}

int main()
{
	auto lines = aoc::read_lines("src/years/2025/day02/input/input.txt");

	// Part 1
	long long sum_invalid_ids = solvePart1(lines);
	std::cout << "Part 1: " << sum_invalid_ids << "\n";

	// Part 2
	sum_invalid_ids = solvePart2(lines);
	std::cout << "Part 2: " << sum_invalid_ids << "\n";
}
