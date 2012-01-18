#include "Control.h"
#include "Error.h"

Control::Control(std::wstring type, Window& parent, const Area& area) : parent(parent), color(Color::BLACK) {
	handle = CreateWindow(
		type.c_str(), L"",
		WS_CHILD | WS_VISIBLE,
		area.x, area.y, area.width, area.height,
		parent.getHandle(), NULL, GetModuleHandle(NULL), NULL
	);

	if (handle == NULL)
		throw WindowsException(L"Control creation failed.");

	parent.addMessageObserver(this);
}

Control::~Control() {
	parent.removeMessageObserver(this);

	DestroyWindow(handle);
}

void Control::setColor(Color color) {
	this->color = color;
	InvalidateRgn(handle, NULL, false);
	UpdateWindow(handle);
}

void Control::setFont(const Font& font) {
	SendMessage(handle, WM_SETFONT, reinterpret_cast<WPARAM>(static_cast<HFONT>(font)), 0);
}

void Control::onMessage(const Message& msg) {
	if (msg.msg == WM_CTLCOLORSTATIC && reinterpret_cast<HWND>(msg.lParam) == handle) {
		HDC hDC = reinterpret_cast<HDC>(msg.wParam);
		SetTextColor(hDC, color);
		SetBkMode(hDC, TRANSPARENT);
	}
}