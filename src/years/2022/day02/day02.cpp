// AOC
#include "utils.hpp"

// STD
#include <iostream>

enum RPSTypes
{
	ROCK = 1,
	PAPER = 2,
	SCISSOR = 3,
	INVALID_TYPE = -1
};

enum RPSResults
{
	LOSS = 0,
	DRAW = 3,
	WIN = 6,
	INVALID_RESULT = -1
};

RPSTypes getRPSType(const char input)
{
	if (input == 'A' || input == 'X')
	{
		return ROCK;
	}
	if (input == 'B' || input == 'Y')
	{
		return PAPER;
	}
	if (input == 'C' || input == 'Z')
	{
		return SCISSOR;
	}

	return INVALID_TYPE;
}

int solvePart1(const std::vector<std::string> &lines, const std::vector<std::vector<int>> &possible_outcomes)
{
	int score = 0;

	for (const auto &line : lines)
	{
		const char opponent = line[0];
		const char player = line[2];
		const RPSTypes opp_RPS = getRPSType(opponent);
		const RPSTypes player_RPS = getRPSType(player);

		for (const auto &outcome : possible_outcomes)
		{
			if (opp_RPS == outcome[0] && player_RPS == outcome[1])
			{
				score += player_RPS + outcome[2];
			}
		}
	}

	return score;
}

RPSResults getRPSResult(const char input)
{
	if (input == 'X')
	{
		return LOSS;
	}
	if (input == 'Y')
	{
		return DRAW;
	}
	if (input == 'Z')
	{
		return WIN;
	}

	return INVALID_RESULT;
}
int solvePart2(const std::vector<std::string> &lines, const std::vector<std::vector<int>> &possible_outcomes)
{
	int score = 0;

	for (const auto &line : lines)
	{
		const char opponent = line[0];
		const char desired_result = line[2];
		const RPSTypes opp_RPS = getRPSType(opponent);
		const RPSResults desired_result_RPS = getRPSResult(desired_result);

		for (const auto &outcome : possible_outcomes)
		{
			if (opp_RPS == outcome[0] && desired_result_RPS == outcome[2])
			{
				score += outcome[1] + outcome[2];
			}
		}
	}

	return score;
}

int main()
{
	const auto lines = aoc::readLines("src/years/2022/day02/input/input.txt");

	const std::vector<std::vector<int>> possible_outcomes = {
		{ROCK, ROCK, DRAW},	  {ROCK, PAPER, WIN},	  {ROCK, SCISSOR, LOSS},
		{SCISSOR, ROCK, WIN}, {SCISSOR, PAPER, LOSS}, {SCISSOR, SCISSOR, DRAW},
		{PAPER, ROCK, LOSS},  {PAPER, PAPER, DRAW},	  {PAPER, SCISSOR, WIN},
	};

	// Part 1
	int score = solvePart1(lines, possible_outcomes);
	std::cout << "Part 1: " << score << "\n";

	// Part 2
	score = solvePart2(lines, possible_outcomes);
	std::cout << "Part 2: " << score << "\n";

	return 0;
}
