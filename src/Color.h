#pragma once
#include <windows.h>

/**
 * RGB color.
 */

class Color {
public:
	Color(BYTE red, BYTE green, BYTE blue) : red(red), green(green), blue(blue){}
	operator COLORREF() const { return RGB(red, green, blue); }
	static const Color WHITE;
	static const Color BLACK;
	static const Color RED;
	static const Color GREEN;
	static const Color BLUE;
private:
	BYTE red;
	BYTE green;
	BYTE blue;
};