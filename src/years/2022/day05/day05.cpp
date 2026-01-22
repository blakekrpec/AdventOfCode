// AOC
#include "utils.hpp"

// STD
#include <cctype>
#include <iostream>
#include <sstream>
#include <stack>
#include <string>

using ContainerStack = std::vector<std::stack<char>>;

struct MoveInstruction
{
	int amount;
	int from;
	int to;
};

int findStackNumberLine(const std::vector<std::string> &lines)
{
	for (size_t i = 0; i < lines.size(); i++)
	{
		const auto line = lines[i];
		for (const char c : line)
		{
			if (c == '[')
			{
				break;
			}
			else if (c == '1')
			{
				return i;
			}
		}
	}
	return -1;
}

ContainerStack buildContainerStack(const std::vector<std::string> &lines, int num_container_line, int num_of_stacks)
{
	ContainerStack container_stack(num_of_stacks);

	for (int row = num_container_line - 1; row >= 0; --row)
	{
		const std::string &current_stack_line = lines[row];

		for (int i = 0; i < num_of_stacks; i++)
		{
			int index = 1 + 4 * i;
			if (index < current_stack_line.size() && std::isalpha(current_stack_line[index]))
			{
				container_stack[i].push(current_stack_line[index]);
			}
		}
	}

	return container_stack;
}

std::string getCrateTops(const ContainerStack &container_stack)
{
	std::string tops;

	for (const auto &stack : container_stack)
	{
		tops.push_back(stack.top());
	}
	return tops;
}

void processMovesPt1(ContainerStack &container_stack, const std::vector<std::string> &lines, int stack_nums_line_num)
{
	for (int i = stack_nums_line_num + 2; i < lines.size(); i++)
	{
		std::string line = lines[i];
		std::string tmp;
		std::stringstream ss(line);

		MoveInstruction mi;
		ss.ignore(5);
		ss >> mi.amount;
		ss.ignore(6);
		ss >> mi.from;
		ss.ignore(4);
		ss >> mi.to;
		mi.from--;
		mi.to--;

		for (int i = 0; i < mi.amount; i++)
		{
			if (!container_stack[mi.from].empty())
			{
				container_stack[mi.to].push(container_stack[mi.from].top());
				container_stack[mi.from].pop();
			}
		}
	}
}

void processMovesPt2(ContainerStack &container_stack, const std::vector<std::string> &lines, int stack_nums_line_num)
{
	for (int i = stack_nums_line_num + 2; i < lines.size(); i++)
	{
		std::string line = lines[i];
		std::string tmp;
		std::stringstream ss(line);

		MoveInstruction mi;
		ss >> tmp >> mi.amount >> tmp >> mi.from >> tmp >> mi.to;
		mi.from--;
		mi.to--;

		std::stack<char> temp;
		for (int i = 0; i < mi.amount; i++)
		{
			if (!container_stack[mi.from].empty())
			{
				temp.push(container_stack[mi.from].top());
				container_stack[mi.from].pop();
			}
		}
		for (int i = 0; i < mi.amount; i++)
		{
			if (!temp.empty())
			{
				container_stack[mi.to].push(temp.top());
				temp.pop();
			}
		}
	}
}

std::string solvePart1(const std::vector<std::string> &lines)
{

	int stack_nums_line_num = findStackNumberLine(lines);

	std::string stack_nums_line = lines[stack_nums_line_num];

	std::stringstream iss(stack_nums_line);
	int num_of_stacks, last = 0;
	while (iss >> num_of_stacks)
	{
		last = num_of_stacks;
	}

	ContainerStack container_stack = buildContainerStack(lines, stack_nums_line_num, num_of_stacks);

	processMovesPt1(container_stack, lines, stack_nums_line_num);

	std::string top_crates = getCrateTops(container_stack);

	return top_crates;
}

std::string solvePart2(const std::vector<std::string> &lines)
{

	int stack_nums_line_num = findStackNumberLine(lines);

	std::string stack_nums_line = lines[stack_nums_line_num];

	std::stringstream iss(stack_nums_line);
	int num_of_stacks, last = 0;
	while (iss >> num_of_stacks)
	{
		last = num_of_stacks;
	}

	ContainerStack container_stack = buildContainerStack(lines, stack_nums_line_num, num_of_stacks);

	processMovesPt2(container_stack, lines, stack_nums_line_num);

	std::string top_crates = getCrateTops(container_stack);

	return top_crates;
}

int main()
{
	const auto lines = aoc::readLines("src/years/2022/day05/input/input.txt");

	std::string top_crates = solvePart1(lines);
	std::cout << "Part 1: " << top_crates << "\n";

	top_crates = solvePart2(lines);
	std::cout << "Part 2: " << top_crates << "\n";
	return 0;
}
