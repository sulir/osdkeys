#pragma once
#include "Message.h"
#include "Window.h"
#include "PopupMenu.h"
#include <string>

/*
 * Notification area icon.
 */

class TrayIcon : public MessageObserver {
public:
	TrayIcon(Window& window, std::wstring tooltip = L"");
	~TrayIcon();
	void setPopupMenu(PopupMenu* menu);
	void onMessage(const Message& msg);
private:
	Window& window;
	UINT iconID;
	UINT messageID;
	PopupMenu* menu;
};