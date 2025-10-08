// AOC
#include "utils.hpp"

// STD
#include <cctype>
#include <cstdint>
#include <iostream>
#include <set>

std::vector<int> getSymbolIndices(const std::string &line)
{
	std::vector<int> symbols_indicies;

	for (int i = 0; i < line.size(); i++)
	{
		const char c = line[i];

		if (!isdigit(c) && c != '.')
		{
			symbols_indicies.push_back(i);
		}
	}
	return symbols_indicies;
}

int getNumberAtIndex(int index, const std::string &str)
{
	int right = index;
	int left = index;

	while (right < str.length() - 1 && isdigit(static_cast<uint32_t>(str[right + 1])))
	{
		right++;
	}
	while (left > 0 && isdigit(static_cast<uint32_t>(str[left - 1])))
	{
		left--;
	}

	return std::stoi(str.substr(left, right - left + 1));
}

std::vector<int> getNumbers(int symbol_index, const std::string &line_above, const std::string &line,
							const std::string &line_below)
{
	std::set<int> unique_numbers;

	auto tryGet = [&](const std::string &str, const int &index)
	{
		if (index >= 0 && index < str.length() && isdigit(static_cast<unsigned char>(str[index])))
		{
			unique_numbers.insert(getNumberAtIndex(index, str));
		}
	};

	for (int i = -1; i <= 1; i++)
	{
		tryGet(line_above, symbol_index + i);
		tryGet(line, symbol_index + i);
		tryGet(line_below, symbol_index + i);
	}

	return {unique_numbers.begin(), unique_numbers.end()};
}

int solvePart1(std::vector<std::string> input)
{
	int sum = 0;

	for (int i = 0; i < input.size(); i++)
	{
		std::string line_above = (i > 0) ? input[i - 1] : "";
		std::string line = input[i];
		std::string line_below = (i < input.size() - 1) ? input[i + 1] : "";

		std::vector<int> symbol_indices = getSymbolIndices(line);

		for (const auto &symbol_index : symbol_indices)
		{
			std::vector<int> numbers = getNumbers(symbol_index, line_above, line, line_below);
			for (const auto &num : numbers)
			{
				sum += num;
			}
		}
	}
	return sum;
}

std::vector<int> getAstericksIndices(std::string line)
{
	std::vector<int> symbols_indicies;

	for (int i = 0; i < line.size(); i++)
	{
		const char c = line[i];

		if (c == '*')
		{
			symbols_indicies.push_back(i);
		}
	}
	return symbols_indicies;
}

int getGearRatio(int gear_index, const std::string &line_above, const std::string &line, const std::string &line_below)
{
	std::set<int> numbers;

	auto tryGet = [&](const std::string &str, const int &index)
	{
		if (index >= 0 && index < str.length() && isdigit(static_cast<unsigned char>(str[index])))
		{
			numbers.insert(getNumberAtIndex(index, str));
		}
	};

	for (int i = -1; i <= 1; i++)
	{
		tryGet(line_above, gear_index + i);
		tryGet(line, gear_index + i);
		tryGet(line_below, gear_index + i);
	}

	if (numbers.size() != 2)
	{
		return 0;
	}
	else
	{
		auto itr = numbers.begin();
		int first_num = *itr++;
		int second_num = *itr;
		return first_num * second_num;
	}
}

int solvePart2(std::vector<std::string> input)
{
	int sum_gear_ratio = 0;

	for (int i = 0; i < input.size(); i++)
	{
		std::string line_above = (i > 0) ? input[i - 1] : "";
		std::string line = input[i];
		std::string line_below = (i < input.size() - 1) ? input[i + 1] : "";

		std::vector<int> astericks_indices = getAstericksIndices(line);

		for (const auto &astericks_index : astericks_indices)
		{
			int gear_ratio = getGearRatio(astericks_index, line_above, line, line_below);

			sum_gear_ratio += gear_ratio;
		}
	}

	return sum_gear_ratio;
}

int main()
{
	auto lines = aoc::read_lines("src/years/2023/day03/input/input.txt");

	// Part 1
	int sum = solvePart1(lines);
	std::cout << "Part 1 Result: " << sum << "\n";

	// Part 2
	int gear_ratio = solvePart2(lines);
	std::cout << "Part 2 Result: " << gear_ratio << "\n";

	return 0;
}
