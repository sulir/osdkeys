#pragma once
#include "Message.h"
#include "Window.h"
#include <string>
#include <map>
#include <functional>
#include <windows.h>

/**
 * Pop-up (context) menu.
 */

class PopupMenu : public MessageObserver {
public:
	PopupMenu(Window& window);
	~PopupMenu();
	void addItem(std::wstring label, std::function<void()> action);
	void show();
	void onMessage(const Message& msg);
private:
	Window& window;
	HMENU menuHandle;
	std::map<UINT_PTR, std::function<void()> > itemActions;
};