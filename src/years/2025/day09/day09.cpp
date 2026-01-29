// AOC
#include "utils.hpp"

// STD
#include <iostream>
#include <string>
#include <vector>

struct Point
{
	int x;
	int y;

	Point(int x_in, int y_in)
	{
		x = x_in;
		y = y_in;
	}

	// Constructor that can take in "x, y" strings.
	explicit Point(const std::string &str)
	{
		int points[2]{0};

		std::vector<std::string> temp = aoc::split(str, ',');
		if (temp.size() != 2)
		{
			std::cerr << "Invalid point string: " << str << '\n';
			return;
			return;
		}
		x = std::stoi(temp[0]);
		y = std::stoi(temp[1]);
	}

	Point() : x(0), y(0)
	{
	}
};

struct Edge
{
	Point src;
	Point dest;

	Edge(Point p1, Point p2)
	{
		src = p1;
		dest = p2;
	}

	Edge() : src(), dest()
	{
	}
};

struct Rectangle
{
	Point bl; // Bottom left.
	Point br; // Bottom right.
	Point tl; // Top left.
	Point tr; // Top right.

	Rectangle(const Point corner1, const Point corner2)
	{
		int min_x = std::min(corner1.x, corner2.x);
		int max_x = std::max(corner1.x, corner2.x);
		int min_y = std::min(corner1.y, corner2.y);
		int max_y = std::max(corner1.y, corner2.y);

		bl = Point(min_x, min_y);
		br = Point(max_x, min_y);
		tl = Point(min_x, max_y);
		tr = Point(max_x, max_y);
	}

	Rectangle() : bl(), br(), tl(), tr()
	{
	}

	long long area() const
	{
		long long width = br.x - bl.x;
		long long height = tl.y - bl.y;
		return width * height;
	}
};

long long solvePart1(const std::vector<std::string> &lines)
{
	long long result{0};

	for (size_t i = 0; i < lines.size(); i++)
	{
		for (size_t j = 0; j < lines.size(); j++)
		{
			if (i == j)
			{
				continue;
			}

			Point corner1 = Point(lines[i]);
			Point corner2 = Point(lines[j]);

			long long dx = std::llabs((long long)corner1.x - corner2.x) + 1;
			long long dy = std::llabs((long long)corner1.y - corner2.y) + 1;
			long long area = dx * dy;

			if (area > result)
			{
				result = area;
			}
		}
	}

	return result;
}

bool isValidRectangle(const Rectangle rect)
{
	// Check that all 4 corners of rect are in the polygon, or on an edge.

	// Then check that no edges intersect with our polygon.

	return true;
}

long long solvePart2(const std::vector<std::string> &lines)
{
	// Build all edges of polygon made of red and green tiles, and populate all points.
	std::vector<Edge> edges(lines.size());
	std::vector<Point> points(lines.size());
	for (size_t i = 0; i < lines.size(); i++)
	{
		// Handle final point, build edge back to 0th Point.
		if (i == lines.size() - 1)
		{
			edges.emplace_back(Point(lines[i]), Point(lines[0]));
		}

		points.emplace_back(lines[i]);
	}

	// Build all possible rectangles, check validity and if area is new max area.
	long long area{0};
	for (size_t i = 0; i < points.size(); i++)
	{
		for (size_t j = 0; j < points.size(); j++)
		{
			if (i == j)
			{
				continue;
			}

			const Rectangle rect = Rectangle(points[i], points[j]);

			if (isValidRectangle(rect) && rect.area() > area)
			{
				area = rect.area();
			}
		}
	}

	return area;
}

int main()
{
	auto lines = aoc::readLines("src/years/2025/day09/input/input.txt");

	long long result = solvePart1(lines);
	std::cout << "Part 1: " << result << "\n";
}
