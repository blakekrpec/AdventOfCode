// AOC
#include "utils.hpp"

// STD
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

std::vector<size_t> findPosOfChar(const std::string str, const char c)
{
	std::vector<size_t> positions;

	size_t pos = str.find(c, 0);

	while (pos != std::string::npos)
	{
		positions.push_back(pos);
		pos = str.find(c, pos + 1);
	}

	return positions;
}

size_t findFirstPosOfChar(const std::string str, const char c)
{
	return str.find(c);
}

struct Results
{
	int split_count;
	long long total_timeline;
};

// After solving part1 and part2 separately, combined them here since most of
// the code was redundant.
Results solve(const std::vector<std::string> &lines)
{
	// Return vals.
	int split_count{0};
	long long total_paths{0};

	std::vector<std::unordered_map<size_t, long long>> beam_paths;

	size_t start_position = findFirstPosOfChar(lines[0], 'S');
	if (start_position == std::string::npos)
	{
		std::cout << "Did not find beam start.\n";
		return {0, 0};
	}

	beam_paths.emplace_back();
	beam_paths.back()[start_position] = 1;

	size_t index{0}; // Track index of splitter rows separate from i since
	// the splitters only happen every other row.

	for (int i = 1; i < lines.size(); i++)
	{
		// Only keep even rows since input has empty rows in between splitters.
		if (i % 2 != 0)
		{
			continue;
		}
		index++;

		std::vector<size_t> split_positions = findPosOfChar(lines[i], '^');

		beam_paths.emplace_back();
		const auto &prev_beams = beam_paths[index - 1];
		auto &current_beams = beam_paths[index];

		for (const auto &[beam_pos, count] : prev_beams)
		{
			// Check if beam will hit splitter and update count of split.
			if (std::find(split_positions.begin(), split_positions.end(), beam_pos) != split_positions.end())
			{
				current_beams[beam_pos - 1] += count;
				current_beams[beam_pos + 1] += count;
				split_count++;
			}
			// If didn't hit splitter continue beam.
			else
			{
				current_beams[beam_pos] += count;
			}
		}
	}

	// Count total number of unique paths.
	for (const auto &[col, count] : beam_paths.back())
	{
		total_paths += count;
	}

	return {split_count, total_paths};
}

int main()
{
	auto lines = aoc::readLines("src/years/2025/day07/input/input.txt");

	Results results = solve(lines);
	std::cout << "Part 1: " << results.split_count << "\n";
	std::cout << "Part 2: " << results.total_timeline << "\n";
}
