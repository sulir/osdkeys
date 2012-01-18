#include "TrayIcon.h"
#include "SequentialFactory.h"
#include <windows.h>

using namespace std;

TrayIcon::TrayIcon(Window& window, wstring tooltip) : window(window), menu(NULL) {
	iconID = SequentialFactory<UINT>::next();
	messageID = SequentialFactory<UINT, WM_APP>::next();

	NOTIFYICONDATA nid = {};
	
	nid.cbSize = sizeof nid;
	nid.hWnd = window.getHandle();
	nid.uID = iconID;
	nid.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP;
	nid.uCallbackMessage = messageID;
	nid.hIcon = LoadIcon(NULL, IDI_INFORMATION);

	// MSVC issues a warning that wstring::copy() is deprecated.
	// Using "Secure API" function wcscpy_s in MinGW would require redistributing msvcrtXX.dll.
	#ifdef _MSC_VER
		wcscpy_s(nid.szTip, tooltip.c_str());
	#else
		size_t length = tooltip.copy(nid.szTip, sizeof nid.szTip - 1);
		nid.szTip[length] = '\0';
	#endif

	Shell_NotifyIcon(NIM_ADD, &nid);
}

TrayIcon::~TrayIcon() {
	if (menu != NULL)
		window.removeMessageObserver(this);

	NOTIFYICONDATA nid = {};

	nid.cbSize = sizeof nid;
	nid.hWnd = window.getHandle();
	nid.uID = iconID;

	Shell_NotifyIcon(NIM_DELETE, &nid);
}

void TrayIcon::setPopupMenu(PopupMenu* menu) {
	this->menu = menu;
	window.addMessageObserver(this);
}

void TrayIcon::onMessage(const Message& msg) {
	if (msg.msg == messageID && msg.lParam == WM_RBUTTONUP) {
		if (menu != NULL)
			menu->show();
	}
}