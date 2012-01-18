#pragma once
#include "Window.h"
#include <map>
#include <windows.h>

/**
 * Handles window messages and sends them to appropriate instances.
 *
 * This class provides a workaround for the fact that in WinAPI, WndProc must
 * be a global or static function.
 */

class WndProc {
public:
	static void registerWindow(Window* window);
	static void unregisterWindow(Window* window);
	static LRESULT CALLBACK wndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
private:
	static std::map<HWND, Window*> handleMap;
};