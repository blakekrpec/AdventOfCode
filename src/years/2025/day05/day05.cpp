// AOC
#include "utils.hpp"

// STD
#include <iostream>
#include <string>
#include <vector>

// Iterate and process up to empty line, extracing range pairs.
std::vector<std::pair<long long, long long>> getFreshRanges(const std::vector<std::string> &lines)
{
	std::vector<std::pair<long long, long long>> results{};

	for (const auto &line : lines)
	{
		if (line.empty())
		{
			break;
		}

		size_t hyphen = line.find('-');

		long long lower_bound = std::stoll(line.substr(0, hyphen));
		long long upper_bound = std::stoll(line.substr(hyphen + 1));

		results.emplace_back(lower_bound, upper_bound);
	}

	return results;
}

// Iterate to the empty line, and then start processing Ingredient IDs.
std::vector<long long> getIngredientIDs(const std::vector<std::string> &lines)
{
	std::vector<long long> results{};

	size_t empty_line_index{0};

	while (true)
	{
		if (lines.at(empty_line_index).empty())
		{
			break;
		}
		empty_line_index++;
	}

	for (size_t i = empty_line_index + 1; i < lines.size(); i++)
	{
		results.emplace_back(std::stoll(lines.at(i)));
	}

	return results;
}

// Determine how man ingredient IDs fall in a given fresh ingredient range.
int solvePart1(const std::vector<std::string> &lines)
{
	std::vector<std::pair<long long, long long>> fresh_ID_ranges = getFreshRanges(lines);

	std::vector<long long> ingredient_IDs = getIngredientIDs(lines);

	int fresh_ingredient_count{0};

	for (const auto &id : ingredient_IDs)
	{
		for (const auto &range : fresh_ID_ranges)
		{
			if (id >= range.first && id <= range.second)
			{
				fresh_ingredient_count++;
				break;
			}
		}
	}

	return fresh_ingredient_count;
}

// Determine how many unique possible fresh ingredient IDs exist for given fresh 
// ingredient ranges.
long long solvePart2(const std::vector<std::string> &lines)
{
	std::vector<std::pair<long long, long long>> fresh_ID_ranges = getFreshRanges(lines);

    std::sort(fresh_ID_ranges.begin(), fresh_ID_ranges.end());

    std::vector<std::pair<long long, long long>> merged_ID_ranges;
    merged_ID_ranges.push_back(fresh_ID_ranges[0]);

    // Find overlaps in ranges, and build vector of merged ranges.
    for (size_t i = 1; i < fresh_ID_ranges.size(); i++)
    {
        auto &last_range = merged_ID_ranges.back();
        const auto &current_range = fresh_ID_ranges[i];

        if (last_range.second + 1 >= current_range.first)
        {
            last_range.second = std::max(last_range.second, current_range.second);
        }
        else 
        {
            merged_ID_ranges.push_back(current_range);
        }
    }

    long long possible_fresh_IDs_count{0};

    for (const auto &id : merged_ID_ranges)
    {
        possible_fresh_IDs_count += (id.second - id.first) + 1;
    }

    return possible_fresh_IDs_count;

}

int main()
{
	auto lines = aoc::readLines("src/years/2025/day05/input/input.txt");

	// Part 1
	int result = solvePart1(lines);
	std::cout << "Part 1: " << result << "\n";

	// Part 2
	long long result2 = solvePart2(lines);
	std::cout << "Part 2: " << result2 << "\n";
}
