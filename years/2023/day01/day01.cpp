#include <cctype>
#include <iostream>
#include <string>

#include "utils.hpp"

const std::vector<std::string> NUM_WORDS = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};

int findCalibrationValuesPt1(const std::string &str)
{
	std::string result;

	int index = 0;
	while (!isdigit(str[index]))
	{
		index++;
	}
	result += str[index];

	index = str.size() - 1;
	while (!isdigit(str[index]))
	{
		index--;
	}
	result += str[index];

	return std::stoi(result);
}

int solvePart1(const std::vector<std::string> &lines)
{
	int sum = 0;

	for (auto line : lines)
	{
		sum += findCalibrationValuesPt1(line);
	}
	return sum;
}

int findCalibrationValuesPt2(const std::string &str)
{
	std::string result, l, r;
	l = "";
	r = "";

	int index = 0;
	while (l == "")
	{
		if (isdigit(str[index]))
		{
			l = str[index];
			break;
		}

		for (size_t n = 0; n < NUM_WORDS.size(); n++)
		{
			std::string sub = str.substr(index, NUM_WORDS.at(n).size());
			if (sub.find(NUM_WORDS.at(n)) != std::string::npos)
			{
				l = std::to_string(n + 1);
				break;
			}
		}
		index++;
	}
	result += l;

	index = str.size() - 1;
	while (r == "")
	{
		if (isdigit(str[index]))
		{
			r = str[index];
			break;
		}

		for (size_t n = 0; n < NUM_WORDS.size(); n++)
		{
			std::string sub = str.substr(index, NUM_WORDS.at(n).size());
			if (sub.find(NUM_WORDS.at(n)) != std::string::npos)
			{
				r = std::to_string(n + 1);
				break;
			}
		}
		index--;
	}
	result += r;
	return std::stoi(result);
}

int solvePart2(const std::vector<std::string> &lines)
{
	int sum = 0;

	for (auto line : lines)
	{
		sum += findCalibrationValuesPt2(line);
	}

	return sum;
}

int main()
{
	const auto lines = aoc::read_lines("years/2023/day01/input/input.txt");

	// Part 1
	int sum = solvePart1(lines);
	std::cout << "Part 1: " << sum << "\n";

	// Part 2
	sum = solvePart2(lines);
	std::cout << "Part 2: " << sum << "\n";

	return 0;
}
