// AOC
#include "utils.hpp"

// STD
#include <iostream>
#include <string>
#include <vector>

struct Range {
    int start;
    int end;

    bool contains(const Range &other) const {
        return start <= other.start && end >= other.end;
    }

    bool overlaps(const Range &other) const {
        return start <= other.end && end >= other.start;
    }
};

std::pair<Range, Range> parseLineIntoElfRanges(const std::string &line)
{
    size_t hyphen1 = line.find('-');
    size_t comma = line.find(',', hyphen1);
    size_t hyphen2 = line.find('-', comma);

    Range elf1_range = {std::stoi(line.substr(0, hyphen1)),
                        std::stoi(line.substr(hyphen1 + 1, comma - hyphen1 - 1))};

    Range elf2_range = {std::stoi(line.substr(comma + 1, hyphen2 - comma - 1)),
                        std::stoi(line.substr(hyphen2 + 1))};

    return {elf1_range, elf2_range};
}

int solvePart1(const std::vector<std::string> &lines)
{
    int num_of_contained_pairs = 0;
    for (const auto &line : lines)
    {
        auto elf_ranges = parseLineIntoElfRanges(line);
        Range elf1_range = elf_ranges.first;
        Range elf2_range = elf_ranges.second;

        if (elf1_range.contains(elf2_range) || elf2_range.contains(elf1_range))
        {
            num_of_contained_pairs++;
        }
    }

    return num_of_contained_pairs;
}

int solvePart2(const std::vector<std::string> &lines)
{
    int num_of_overlapped_pairs = 0;
    for (const auto &line : lines)
    {
        auto elf_ranges = parseLineIntoElfRanges(line);
        Range elf1_range = elf_ranges.first;
        Range elf2_range = elf_ranges.second;

        if (elf1_range.overlaps(elf2_range))
        {
            num_of_overlapped_pairs++;
        }
    }

    return num_of_overlapped_pairs;
}

int main()
{
    const auto lines = aoc::read_lines("src/years/2022/day04/input/input.txt");

    int num_of_contained_pairs = solvePart1(lines);
    std::cout << "Part 1: " << num_of_contained_pairs << "\n";

    int num_of_overlapped_pairs = solvePart2(lines);
    std::cout << "Part 2: " << num_of_overlapped_pairs << "\n";

    return 0;
}
