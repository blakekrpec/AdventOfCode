// AOC
#include "utils.hpp"

// STD
#include <algorithm>
#include <cmath>
#include <iostream>
#include <set>
#include <stdexcept>
#include <string>
#include <vector>

struct Point
{
	long long x;
	long long y;
	long long z;

	Point(const std::vector<int> &v)
	{
		if (v.size() != 3)
		{
			throw std::invalid_argument("Vector must have exactly 3 elements to construct Point.");
		}
		x = v[0];
		y = v[1];
		z = v[2];
	}

	Point() : x(0), y(0), z(0)
	{
	}

	bool operator<(const Point &other) const
	{
		if (x != other.x)
			return x < other.x;
		if (y != other.y)
			return y < other.y;
		return z < other.z;
	}

	bool operator==(const Point &other) const
	{
		return x == other.x && y == other.y && z == other.z;
	}
};

// Print Point.
std::ostream &operator<<(std::ostream &os, const Point &p)
{
	os << "Point: (" << p.x << ", " << p.y << ", " << p.z << ")";
	return os;
}

struct Distance
{
	long long dist;
	Point p1;
	Point p2;

	Distance(const Point &a, const Point &b)
	{
		// Handle ordering so pair combos aren't double counted.
		// i.e. Only one distance for both p1->p2 or p2->p1.
		if (b < a)
		{
			p1 = b;
			p2 = a;
		}
		else
		{
			p1 = a;
			p2 = b;
		}

		long long dx = p2.x - p1.x;
		long long dy = p2.y - p1.y;
		long long dz = p2.z - p1.z;
		dist = dx * dx + dy * dy + dz * dz;
	}

	Distance() : dist(0), p1(), p2()
	{
	}

	bool operator<(const Distance &other) const
	{
		if (dist != other.dist)
			return dist < other.dist;

		if (!(p1 == other.p1))
			return p1 < other.p1;

		return p2 < other.p2;
	}
};

// Extract Points from the input.
std::vector<Point> getPointsFromInput(const std::vector<std::string> &lines)
{
	std::vector<Point> coords;

	for (const auto &line : lines)
	{
		std::vector<int> line_vec_ints = aoc::delimStringToVecOfInts(line);
		coords.emplace_back(Point(line_vec_ints));
	}
	return coords;
}

// Given list of points, populate set of distances between all unique point combos.
std::set<Distance> populateDistancesFromPoints(const std::vector<Point> &points)
{
	std::set<Distance> distances;

	for (size_t i = 0; i < points.size(); i++)
	{
		for (size_t j = 0; j < points.size(); j++)
		{
			if (i == j)
			{
				continue;
			}
			distances.emplace(Distance(points[i], points[j]));
		}
	}
	return distances;
}

// Processes a single distance, updating circuits by adding points or merging.
// Returns true if circuits was changed (point added to existing, or new circuit created).
// Returns false if both points were already connected.
bool processDistance(const Distance &dist, std::vector<std::set<Point>> &circuits)
{
	std::vector<size_t> matching_indices;

	for (size_t i = 0; i < circuits.size(); i++)
	{
		if (circuits[i].count(dist.p1) || circuits[i].count(dist.p2))
		{
			matching_indices.push_back(i);
		}
	}

	// Neither point exists in an existing circuit, create new circuit.
	if (matching_indices.empty())
	{
		circuits.push_back({dist.p1, dist.p2});
		return true;
	}

	// Check if both points are already in the same circuit. If so do nothing and return false.
	if (matching_indices.size() == 1 && circuits[matching_indices[0]].count(dist.p1) &&
		circuits[matching_indices[0]].count(dist.p2))
	{
		return false;
	}

	// Merge all matching circuits into the first one.
	auto &target = circuits[matching_indices[0]];
	target.insert(dist.p1);
	target.insert(dist.p2);

	for (size_t i = matching_indices.size() - 1; i > 0; i--)
	{
		target.insert(circuits[matching_indices[i]].begin(), circuits[matching_indices[i]].end());
		circuits.erase(circuits.begin() + matching_indices[i]);
	}

	return true;
}

// Return circuits state after performing given number of connections.
// Could be unordered set, but would need to implement hashing for Point.
std::vector<std::set<Point>> populateCircuitsFromDistances(const std::set<Distance> &dists,
														   size_t num_connections_to_make)
{
	std::vector<std::set<Point>> circuits;
	size_t num_connections = 0;

	for (const auto &dist : dists)
	{
		if (num_connections >= num_connections_to_make)
		{
			break;
		}

		processDistance(dist, circuits);

		num_connections++;
	}

	return circuits;
}

// Perform connections until all points are connected in single circuit. Return the final ponit that when connected
// results in full connection.
std::pair<Point, Point> findConnectionWhereFullyConnected(const std::set<Distance> &dists, size_t num_total_points)
{
	std::vector<std::set<Point>> circuits;

	for (const auto &dist : dists)
	{
		processDistance(dist, circuits);

		if (circuits.size() == 1 && circuits[0].size() == num_total_points)
		{
			return {dist.p1, dist.p2};
		}
	}

	// Should never reach here if input is valid... hopefully.
	return {};
}

long long solvePart1(const std::vector<std::string> &lines, size_t num_connections)
{
	const auto points = getPointsFromInput(lines);
	const auto distances = populateDistancesFromPoints(points);
	auto circuits = populateCircuitsFromDistances(distances, num_connections);

	std::sort(circuits.begin(), circuits.end(), [](const auto &a, const auto &b) { return a.size() > b.size(); });

	long long result = 1;
	for (size_t i = 0; i < 3; i++)
	{
		result *= circuits[i].size();
	}

	return result;
}

long long solvePart2(const std::vector<std::string> &lines)
{
	const auto points = getPointsFromInput(lines);
	const auto distances = populateDistancesFromPoints(points);
	auto [p1, p2] = findConnectionWhereFullyConnected(distances, points.size());

	return p1.x * p2.x;
}

int main()
{
	auto lines = aoc::readLines("src/years/2025/day08/input/input.txt");

	// Part 1
	long long result = solvePart1(lines, 1000);
	std::cout << "Part 1: " << result << "\n";

	// // Part 2
	long long result2 = solvePart2(lines);
	std::cout << "Part 2: " << result2 << "\n";
}
