// AOC
#include "utils.hpp"

// STD
#include <iostream>
#include <string>

std::vector<char> getOperations(const std::vector<std::string> &lines)
{
	// Last row contains the operations.
	const std::string &signs = lines.back();

	std::vector<char> operations{};

	for (char c : signs)
	{
		if (c == '+' || c == '*')
		{
			operations.emplace_back(c);
		}
	}

	return operations;
}

std::vector<std::vector<std::string>> getInputs(const std::vector<std::string> &lines)
{
	// Vector has lines.size() - 1 rows (final row is operaton).
	std::vector<std::vector<std::string>> inputs(lines.size() - 1);

	// Get max length of a line, but they should all be uniform.
	size_t max_len_line{0};
	for (const auto &line : lines)
	{
		max_len_line = std::max(max_len_line, line.length());
	}

	// A ' ' is a delimeter when its a ' ' in all rows. Find and store all delimeter locations.
	std::vector<size_t> delims;
	for (size_t col = 0; col < max_len_line; col++)
	{
		bool is_delim = true;
		for (size_t row = 0; row < lines.size(); row++)
		{
			if (lines[row][col] != ' ')
			{
				is_delim = false;
				break;
			}
		}

		if (is_delim)
		{
			delims.push_back(col);
		}
	}

	// Grab the strings between delim locations, in each row;
	size_t start{0};
	for (size_t delim_index = 0; delim_index < delims.size(); delim_index++)
	{
		size_t delim = delims[delim_index];
		for (size_t row = 0; row < lines.size() - 1; row++)
		{
			inputs[row].emplace_back(lines[row].substr(start, delim - start));
		}
		start = delim + 1;
	}

	// Capture the final segment after the final delim.
	for (size_t row = 0; row < lines.size() - 1; row++)
	{
		inputs[row].push_back(lines[row].substr(start));
	}

	return inputs;
}

long long solvePart1(const std::vector<std::string> &lines)
{
	std::vector<char> operations = getOperations(lines);
	std::vector<std::vector<std::string>> inputs = getInputs(lines);

	// Do math operations per part 1 rules, and sum the results;
	long long sum{0};
	long long result{0};
	for (size_t i = 0; i < operations.size(); i++)
	{
		long long result = (operations[i] == '+') ? 0 : 1;
		if (operations[i] == '+')
		{
			// sum all of inputs [i]
			for (size_t j = 0; j < inputs.size(); j++)
			{
				result += std::stoll(inputs[j][i]);
			}
		}
		else if (operations[i] == '*')
		{
			// multiply all of inputs [i]
			for (size_t j = 0; j < inputs.size(); j++)
			{
				result *= std::stoll(inputs[j][i]);
			}
		}
		sum += result;
	}

	return sum;
}

long long solvePart2(const std::vector<std::string> &lines)
{
	std::vector<char> operations = getOperations(lines);
	std::vector<std::vector<std::string>> inputs = getInputs(lines);

	long long sum = 0;

	// Loop over operation sets we will do.
	for (size_t op = 0; op < operations.size(); op++)
	{
		std::vector<std::string> operation_numbers; // Numbers to do the operation (+ or *) with.
		operation_numbers.reserve(inputs.size());

		// Build sets of columns of input numbers.
		for (size_t row = 0; row < inputs.size(); row++)
		{
			operation_numbers.push_back(inputs[row][op]);
		}

		// If adding reset op_result to 0, if multiplying set to 1 (so we don't just multiply to 0).
		long long result = (operations[op] == '+') ? 0 : 1;

		// Build the numbers reading vertically per puzzle rules.
		// Iterate over each index of the operation numbers (columns).
		for (size_t col = 0; col < operation_numbers[0].size(); col++)
		{
			std::string temp;

			// Iterate over each row of inputs.
			for (size_t num_index = 0; num_index < inputs.size(); num_index++)
			{
				const char c = operation_numbers[num_index][col];
				if (c != ' ')
				{
					temp.push_back(c);
				}
			}

			long long num = std::stoll(temp);

			if (operations[op] == '+')
			{
				result += num;
			}
			else if (operations[op] == '*')
			{
				result *= num;
			}
		}

		sum += result;
	}

	return sum;
}

int main()
{
	auto lines = aoc::readLines("src/years/2025/day06/input/input.txt");

	// Part 1
	long long result = solvePart1(lines);
	std::cout << "Part 1: " << result << "\n";

	result = solvePart2(lines);
	std::cout << "Part 2: " << result << "\n";
}
