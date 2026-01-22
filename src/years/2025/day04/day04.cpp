// AOC
#include "utils.hpp"

// STD
#include <iostream>
#include <string>

// clang-format off
constexpr int NEIGHBOR_DIRS[8][2] = 
        {{-1, 1}, {0,  1}, {1, 1},
        {-1,  0},          {1, 0},
        {-1, -1}, {0, -1}, {1, -1}};
// clang-format on

bool isCharRoll(const char &c)
{
	return (c == '@');
}

// Count how many of the 8 neighboring cells are rolls (is an @).
int countNeighborRolls(const std::vector<std::string> &grid, int row, int col)
{
	int rows = static_cast<int>(grid.size());
	int cols = static_cast<int>(grid.at(0).size());
	int count{0};

	for (const auto &dir : NEIGHBOR_DIRS)
	{
		int row_mod = row + dir[0];
		int col_mod = col + dir[1];

		// If the neighbor cell exists and can be checked
		if (row_mod >= 0 && row_mod < rows && col_mod >= 0 && col_mod < cols)
		{
			if (isCharRoll(grid.at(row_mod).at(col_mod)))
			{
				count++;
			}
		}
	}
	return count;
}

// Return a vector of pair<int, int> of coordinates of rolls that can be accessed.
std::vector<std::pair<int, int>> findAccessibleRolls(const std::vector<std::string> &grid, int num_neighbors = 4)
{
	std::vector<std::pair<int, int>> result;

	int rows = static_cast<int>(grid.size());
	int cols = static_cast<int>(grid[0].size());

	for (size_t i = 0; i < rows; i++)
	{
		for (size_t j = 0; j < cols; j++)
		{
			// If grid cell is a roll check, no need to check non roll cells.
			if (isCharRoll(grid.at(i).at(j)))
			{
				if (countNeighborRolls(grid, i, j) < num_neighbors)
				{
					result.emplace_back(i, j);
				}
			}
		}
	}

	return result;
}

// Count number of rolls that are accessible.
int solvePart1(const std::vector<std::string> &lines)
{
	return static_cast<int>(findAccessibleRolls(lines).size());
}

// Count number of rolls accessible, remove them, and repeat until no more rolls can be removed.
// Return total rolls removed.
int solvePart2(std::vector<std::string> &lines)
{
	int total_removed{0};

	while (true)
	{
		auto to_remove = findAccessibleRolls(lines);
		if (to_remove.empty())
		{
			break;
		}

		for (const auto &[i, j] : to_remove)
		{
			lines.at(i).at(j) = 'x';
		}

		total_removed += static_cast<int>(to_remove.size());
	}
	return total_removed;
}

int main()
{
	auto lines = aoc::readLines("src/years/2025/day04/input/input.txt");

	// Part 1
	int result = solvePart1(lines);
	std::cout << "Part 1: " << result << "\n";

	// Part 2
	int result2 = solvePart2(lines);
	std::cout << "Part 2: " << result2 << "\n";
}
