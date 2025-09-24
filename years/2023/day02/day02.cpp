#include "utils.hpp"

#include <cctype>
#include <cstddef>
#include <iostream>
#include <stdexcept>

using GameNumAndInfo = std::pair<size_t, std::string>;
using NumColorPair = std::pair<size_t, std::string>;
using DrawResult = std::vector<NumColorPair>;
using GameResult = std::vector<DrawResult>;

constexpr int RED_NUM = 12;
constexpr int GREEN_NUM = 13;
constexpr int BLUE_NUM = 14;

GameNumAndInfo extractGameNumAndInfo(const std::string &input)
{
	auto colon = input.find(':');
	if (colon == std::string::npos)
	{
		throw std::runtime_error("No colon(:) found input.");
	}

	size_t start = colon;
	size_t end = colon;
	while (start > 0 && std::isdigit(input[start - 1]))
	{
		start--;
	}

	size_t game_num = std::stoul(input.substr(start, end - start));

	// fine game info
	std::string game_info = input.substr(colon + 2);

	GameNumAndInfo result = {game_num, game_info};
	return result;
}

GameResult unpackGameInfoToGameResult(const GameNumAndInfo &game_num_info)
{
	GameResult result;

	const std::string &info = game_num_info.second;
	size_t start = 0;
	size_t end = 0;

	while (end != std::string::npos)
	{
		end = info.find(';', start);
		std::string draw_str = info.substr(start, end - start);
		start = (end == std::string::npos) ? end : end + 1;

		DrawResult draw;
		std::istringstream iss(draw_str);
		std::string token;

		while (std::getline(iss, token, ','))
		{
			size_t pos = 0;
			while (pos < token.size() && std::isspace(token[pos]))
				pos++;
			token = token.substr(pos);

			size_t space = token.find(' ');
			if (space == std::string::npos)
				continue;

			size_t number = std::stoul(token.substr(0, space));
			std::string color = token.substr(space + 1);

			draw.emplace_back(number, color);
		}

		result.push_back(draw);
	}
	return result;
}

bool isGamePossible(GameResult game_result)
{
	for (const auto &draw_result : game_result)
	{
		size_t red = 0;
		size_t green = 0;
		size_t blue = 0;
		for (const auto &num_color_pair : draw_result)
		{
			if (num_color_pair.second == "red")
			{
				red += num_color_pair.first;
			}
			else if (num_color_pair.second == "green")
			{
				green += num_color_pair.first;
			}
			else if (num_color_pair.second == "blue")
			{
				blue += num_color_pair.first;
			}
		}
		if (red > RED_NUM || green > GREEN_NUM || blue > BLUE_NUM)
		{
			return false;
		}
	}
	return true;
}

int computePower(const GameResult &game_result)
{
	size_t red = 0;
	size_t green = 0;
	size_t blue = 0;
	size_t power = 0;

	for (const auto &draw : game_result)
	{
		for (const auto &num_color_pair : draw)
		{
			if (num_color_pair.second == "red")
			{
				red = std::max(red, num_color_pair.first);
			}
			else if (num_color_pair.second == "green")
			{
				green = std::max(green, num_color_pair.first);
			}
			else if (num_color_pair.second == "blue")
			{
				blue = std::max(blue, num_color_pair.first);
			}
		}
	}
	return power = ((red == 0) ? 1 : red) * ((blue == 0) ? 1 : blue) * ((green == 0) ? 1 : green);
}

int main()
{
	const auto lines = aoc::read_lines("years/2023/day02/input/input.txt");

	// Part 1
	size_t sum = 0;
	for (const auto &line : lines)
	{
		GameNumAndInfo game_num_info = extractGameNumAndInfo(line);
		GameResult game_result = unpackGameInfoToGameResult(game_num_info);
		if (isGamePossible(game_result))
		{
			sum += game_num_info.first;
		}
	}
	std::cout << "Part 1 Result: " << sum << "\n";

	// Part 2
	size_t power_sum = 0;

	for (const auto &line : lines)
	{
		GameNumAndInfo game_num_info = extractGameNumAndInfo(line);
		GameResult game_result = unpackGameInfoToGameResult(game_num_info);
		power_sum += computePower(game_result);
	}
	std::cout << "Part 2 Result: " << power_sum << "\n";

    return 0;
}
