// AOC
#include "utils.hpp"

// STD
#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>

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

int solvePart1(const std::vector<std::string> &lines)
{
	std::vector<std::pair<long long, long long>> fresh_ID_ranges = getFreshRanges(lines);

	// for (const auto &pair : fresh_ID_ranges)
	// {
	// 	std::cout << "pair: " << pair.first << " - " << pair.second << "\n";
	// }

	std::vector<long long> ingredient_IDs = getIngredientIDs(lines);

	// for (const auto &id : ingredient_IDs)
	// {
	// 	std::cout << "id: " << id << "\n";
	// }

	int fresh_ingredient_count{0};

	for (const auto &id : ingredient_IDs)
	{
		for (const auto &range : fresh_ID_ranges)
		{
			if (id >= range.first && id <= range.second)
			{
				fresh_ingredient_count++;
				// std::cout << "ID: " << id << " is fresh. In range: " << range.first << " - " << range.second << "\n";
				// std::cout << "New fresh_ing_count is " << fresh_ingredient_count << "\n";
				// std::cout << "\n";
				break;
			}
			// else
			// {
			// 	std::cout << "ID: " << id << " did not fall in range: " << range.first << " - " << range.second << "\n";
			// 	std::cout << "\n";
			// }
		}
	}

	return fresh_ingredient_count;
}

long long solvePart2(const std::vector<std::string> &lines)
{
	std::vector<std::pair<long long, long long>> fresh_ID_ranges = getFreshRanges(lines);

	std::unordered_set<long long> possible_fresh_IDs{};

	for (const auto &id : fresh_ID_ranges)
	{
		for (long long i = id.first; i <= id.second; i++)
		{
			possible_fresh_IDs.emplace(i);
		}
	}

	long long possible_fresh_IDs_count{0};

	for (const auto &id : possible_fresh_IDs)
	{
		possible_fresh_IDs_count += id;
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
