#pragma once
#include <string>
#include <windows.h>

/**
 * WinAPI font with basic properties.
 */

class Font {
public:
	Font(std::wstring face, int height, bool bold = false, bool italic = false, bool underline = false);
	~Font();
	operator HFONT() const { return fontHandle; }
private:
	HFONT fontHandle;
};