#pragma once
#include "GuiElement.h"
#include "Message.h"
#include "Color.h"
#include "Area.h"
#include <string>
#include <set>
#include <windows.h>

/**
 * Overlapped window in WinAPI terminology.
 */

class Window : public GuiElement {
public:
	Window(const std::wstring name, const Area& area, Color background = Color(0, 0, 0));
	~Window();
	void addMessageObserver(MessageObserver* observer);
	void removeMessageObserver(MessageObserver* observer);
	LRESULT wndProc(UINT msg, WPARAM wParam, LPARAM lParam);
private:
	void createWindowClass();
	void createWindow();
	std::wstring name;
	Area area;
	HBRUSH backgroundBrush;
	int atom;
	std::set<MessageObserver*> messageObservers;
};