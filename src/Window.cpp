#include "Window.h"
#include "Error.h"
#include "SequentialFactory.h"
#include "WndProc.h"

using namespace std;

Window::Window(const wstring name, const Area& area, Color background) : name(name), area(area) {
	backgroundBrush = CreateSolidBrush(background);

	atom = SequentialFactory<int, 1>::next();
	createWindowClass();
	createWindow();
	WndProc::registerWindow(this);
}

Window::~Window() {
	WndProc::unregisterWindow(this);
	DestroyWindow(handle);
	UnregisterClass(MAKEINTATOM(atom), 0);

	DeleteObject(backgroundBrush);
}

void Window::addMessageObserver(MessageObserver* observer) {
	messageObservers.insert(observer);
}

void Window::removeMessageObserver(MessageObserver* observer) {
	messageObservers.erase(observer);
}

LRESULT Window::wndProc(UINT msg, WPARAM wParam, LPARAM lParam) {
	const Message message(msg, wParam, lParam);
	
	auto iter = messageObservers.begin();

	// The observer may remove the current element from the set by calling removeMessageObserver()
	// inside its onMessage() method. We must pass it only a copy of the iterator, while the main
	// one is already incremented.
	while (iter != messageObservers.end()) {
		auto current = iter++;
		(*current)->onMessage(message);
	}
	
	if (msg == WM_CTLCOLORSTATIC)
		return (INT_PTR)GetStockObject(BLACK_BRUSH);
	else
		return DefWindowProc(handle, msg, wParam, lParam);
}

void Window::createWindowClass() {
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = 0;
	wc.lpfnWndProc = WndProc::wndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = GetModuleHandle(NULL);
	wc.hIcon = LoadIcon(NULL, IDI_INFORMATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = MAKEINTATOM(atom);
	wc.hIconSm = LoadIcon(NULL, IDI_INFORMATION);
	
	if (!RegisterClassEx(&wc))
		throw WindowsException(L"Window class registration failed.");
}

void Window::createWindow() {
	handle = CreateWindowEx(
		WS_EX_NOACTIVATE | WS_EX_TOPMOST,
		MAKEINTATOM(atom),
		name.c_str(),
		WS_POPUP,
		area.x, area.y, area.width, area.height,
		NULL, NULL, GetModuleHandle(NULL), NULL
	);

	if (handle == NULL)
		throw WindowsException(L"Window creation failed.");
}