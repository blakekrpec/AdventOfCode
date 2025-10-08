// AOC
#include "utils.hpp"

// STD
#include <iostream>
#include <sstream>
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

int computeNumberOfMatches(const CardLine &card_line)
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
	return matches;
}

int solvePart1(const std::vector<std::string> &lines)
{
	int result = 0;
	std::vector<CardLine> card_lines = processScratchCard(lines);

	for (const auto &card_line : card_lines)
	{
		int matches = computeNumberOfMatches(card_line);
		result += pow(2, matches - 1);
	}
	return result;
}

int solvePart2(const std::vector<std::string> &lines)
{
	int num_cards = 0;
	std::vector<int> num_of_each_card(lines.size(), 1);

	std::vector<CardLine> card_lines = processScratchCard(lines);

	for (int i = 0; i < card_lines.size(); i++)
	{
		int matches = computeNumberOfMatches(card_lines.at(i));
		int end = std::min((int)num_of_each_card.size() - 1, i + matches);
		for (int j = i + 1; j <= end; j++)
		{
			num_of_each_card.at(j) += num_of_each_card.at(i);
		}
	}

	for (int i = 0; i < num_of_each_card.size(); i++)
	{
		num_cards += num_of_each_card.at(i);
	}
	return num_cards;
}

int main()
{
	const auto lines = aoc::read_lines("src/years/2023/day04/input/input.txt");

	int points = solvePart1(lines);
	std::cout << "Part 1: " << points << "\n";

	int num_cards = solvePart2(lines);
	std::cout << "Part 2: " << num_cards << "\n";

	return 0;
}
