// AOC
#include "utils.hpp"

// STD
#include <algorithm>
#include <array>
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

	std::array<const Point *, 4> corners() const
	{
		return {&bl, &br, &tl, &tr};
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

// Return if a ponit is on a given edge.
bool pointOnEdge(const Point &p, const Edge &e)
{
	const int min_x = std::min(e.dest.x, e.src.x);
	const int max_x = std::max(e.dest.x, e.src.x);
	const int min_y = std::min(e.dest.y, e.src.y);
	const int max_y = std::max(e.dest.y, e.src.y);

	// Vertical edge.
	if (e.src.x == e.dest.x && p.x == e.src.x)
	{
		return p.y <= max_y && p.y >= min_y;
	}

	// Horizontal edge.
	if (e.src.y == e.dest.y && p.y == e.src.y)
	{
		return p.x <= max_x && p.x >= min_x;
	}
	return false;
}

// Return if a provided point is inside the polygon defined by edges.
bool pointInPolygon(const Point &p, const std::vector<Edge> &edges)
{
	// Check if point is on a boudary.
	for (const auto &edge : edges)
	{
		if (pointOnEdge(p, edge))
		{
			return true;
		}
	}

	// From point, cast a ray to the right, horizontal. If it hits odd edges, its in polygons. If it hits even edges,
	// its outside polygon.
	int crossings{0};
	for (const auto &edge : edges)
	{
		// Horizontal ray can only cross vertical edges. Skip horizontal ones.
		if (edge.src.x == edge.dest.x)
		{
			const int min_y = std::min(edge.src.y, edge.dest.y);
			const int max_y = std::max(edge.src.y, edge.dest.y);

			// If edge is to right, and ray crosses it increment crossings.
			if (p.x < edge.src.x && min_y < p.y && max_y > p.y)
			{
				crossings++;
			}
		}
	}

	// If crossed odd number of edges, in polygon, if crossed even numer of edges, out of polygon.
	return crossings % 2 == 1;
}

// Return if an edge intersects into a rectangle.
bool edgeInterectsRect(const Rectangle &rect, const Edge &edge)
{
	// Horizontal edge.
	if (edge.src.y == edge.dest.y)
	{
		const int y = edge.src.y;
		const int edge_x_min = std::min(edge.src.x, edge.dest.x);
		const int edge_x_max = std::max(edge.src.x, edge.dest.x);

		// If y is inside rect's y-range, and edge and rect x ranges overlap.
		if (rect.bl.y < y && y < rect.tl.y && edge_x_min < rect.br.x && rect.bl.x < edge_x_max)
		{
			return true;
		}
	}
	// Vertical edge.
	else
	{
		const int x = edge.src.x;
		const int edge_y_min = std::min(edge.src.y, edge.dest.y);
		const int edge_y_max = std::max(edge.src.y, edge.dest.y);

		// If x is inside rect's x-range, and edge and rect y ranges overlap.
		if (rect.bl.x < x && x < rect.br.x && edge_y_min < rect.tl.y && rect.bl.y < edge_y_max)
		{
			return true;
		}
	}
	return false;
}

// Return if a rectanlge is valid given the rules for Part 2.
bool isValidRectangle(const Rectangle rect, const std::vector<Edge> &edges)
{
	// Check all 4 corners must be inside or on polygon boundary.
	for (const Point *corner : rect.corners())
	{
		if (!pointInPolygon(*corner, edges))
		{
			return false;
		}
	}

	// Check no polygon edge can cut through rectangle's interior.
	for (const auto &edge : edges)
	{
		if (edgeInterectsRect(rect, edge))
		{
			return false;
		}
	}

	return true;
}

long long solvePart2(const std::vector<std::string> &lines)
{
	// Build all edges of polygon made of red and green tiles, and populate all points.
	std::vector<Edge> edges(lines.size());
	std::vector<Point> points(lines.size());
	for (size_t i = 0; i < lines.size(); i++)
	{
		// Build edges, wrapping around final point back to first.
		size_t next = (i + 1) % lines.size();
		edges.emplace_back(Point(lines[i]), Point(lines[next]));

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

			if (isValidRectangle(rect, edges) && rect.area() > area)
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

	result = solvePart2(lines);
	std::cout << "Part 1: " << result << "\n";
}
