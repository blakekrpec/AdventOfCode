#include "utils.hpp"

#include <iostream>
#include <stdexcept>

using CardLine = std::pair<std::vector<int>, std::vector<int>>;

std::vector<int> extractNumbersFromString(const std::string &str)
{
	std::vector<int> nums;

	std::string token;
	std::stringstream ss(str);

	while (getline(ss, token, ' '))
	{
		if (!token.empty())
		{
			nums.push_back(std::stoi(token));
		}
	}

	return nums;
}

std::vector<CardLine> processScratchCard(const std::vector<std::string> &lines)
{
	std::vector<CardLine> card_lines;

	for (const auto &line : lines)
	{
		const size_t colon = line.find_first_of(':');
		const size_t pipe = line.find_first_of('|');

		if (colon == std::string::npos || pipe == std::string::npos)
		{
			throw std::runtime_error("Failed to fine colon or pipe.");
		}
		std::string winning_numbers_str = line.substr(colon + 1, pipe - (colon + 1));
		std::string playing_numbers_str = line.substr(pipe + 1);

		card_lines.push_back(
			{extractNumbersFromString(winning_numbers_str), extractNumbersFromString(playing_numbers_str)});
	}

	return card_lines;
}
int computeScoreOfLine(const CardLine &card_line)
{
	int matches = 0;
	for (const auto &play_num : card_line.second)
	{
		for (const auto &win_num : card_line.first)
		{
			if (play_num == win_num)
			{
				matches++;
			}
		}
	}
	return pow(2, matches - 1);
}

int solvePart1(const std::vector<std::string> &lines)
{
	int result = 0;
	std::vector<CardLine> card_lines = processScratchCard(lines);

	for (const auto &card_line : card_lines)
	{
		result += computeScoreOfLine(card_line);
	}
	return result;
}

int main()
{
	const auto lines = aoc::read_lines("years/2023/day04/input/input.txt");

	int points = solvePart1(lines);
	std::cout << "Part 1: " << points << "\n";

    return 0;
}
