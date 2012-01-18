#include "Font.h"

Font::Font(std::wstring face, int height, bool bold, bool italic, bool underline) : fontHandle(NULL) {
	fontHandle = CreateFont(
		height, 0, 0, 0,
		bold ? FW_BOLD : FW_NORMAL, italic, underline, FALSE,
		DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH, face.c_str()
	);
}

Font::~Font() {
	if (fontHandle != NULL)
		DeleteObject(fontHandle);
}