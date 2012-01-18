#pragma once

/**
 * Two-dimensional rectangular area with position, width and height.
 */

struct Area {
public:
	Area(int x, int y, int width, int height) : x(x), y(y), width(width), height(height) {}
	const int x;
	const int y;
	const int width;
	const int height;
};