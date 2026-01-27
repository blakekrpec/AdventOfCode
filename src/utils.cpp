#include "utils.hpp"

// STD
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

namespace aoc
{

std::vector<std::string> readLinesSkipEmpties(const std::string &filename)
{
	std::ifstream file(filename);
	std::vector<std::string> lines;
	std::string line;
	while (std::getline(file, line))
	{
		if (!line.empty())
			lines.push_back(line);
	}
	return lines;
}

std::vector<std::string> readLines(const std::string &filename)
{
	std::ifstream file(filename);
	std::vector<std::string> lines;
	std::string line;
	while (std::getline(file, line))
	{
		lines.push_back(line);
	}
	return lines;
}

std::vector<int> readLinesAsInts(const std::string &filename)
{
	std::ifstream file(filename);
	std::vector<int> lines;
	std::string line;
	while (std::getline(file, line))
	{
		if (!line.empty())
		{
			lines.push_back(std::stoi(line));
		}
	}
	return lines;
}

std::vector<int> readLinesAsIntsEmptyAsZero(const std::string &filename)
{
	std::ifstream file(filename);
	std::vector<int> lines;
	std::string line;
	while (std::getline(file, line))
	{
		if (!line.empty())
		{
			lines.push_back(std::stoi(line));
		}
		else
		{
			lines.push_back(0);
		}
	}
	return lines;
}

std::vector<int> delimStringToVecOfInts(const std::string &str, char delim)
{
	std::vector<int> result;
	for (const auto &token : split(str, delim))
	{
		if (!token.empty())
			result.push_back(std::stoi(token));
	}
	return result;
}

std::vector<std::string> split(const std::string &s, char delimiter)
{
	std::vector<std::string> tokens;
	std::stringstream ss(s);
	std::string item;
	while (std::getline(ss, item, delimiter))
	{
		tokens.push_back(item);
	}
	return tokens;
}

std::string trim(const std::string &s)
{
	const char *whitespace = " \t\n\r";
	size_t start = s.find_first_not_of(whitespace);
	if (start == std::string::npos)
	{
		return "";
	}
	size_t end = s.find_last_not_of(whitespace);
	return s.substr(start, end - start + 1);
}
} // namespace aoc
