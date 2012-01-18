#include "WndProc.h"

using namespace std;

void WndProc::registerWindow(Window* window) {
	handleMap[window->getHandle()] = window;
}

void WndProc::unregisterWindow(Window* window) {
	handleMap.erase(window->getHandle());
}

LRESULT CALLBACK WndProc::wndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	// Similar to http://stackoverflow.com/questions/3380294/object-oriented-c-win32.
	map<HWND, Window*>::iterator it = handleMap.find(hWnd);
	
	if (it != handleMap.end())
		return it->second->wndProc(msg, wParam, lParam);
	else
		return DefWindowProc(hWnd, msg, wParam, lParam);
}

map<HWND, Window*> WndProc::handleMap;