#include "PopupMenu.h"
#include "SequentialFactory.h"

using namespace std;

PopupMenu::PopupMenu(Window& window) : window(window) {
	menuHandle = CreatePopupMenu();
	window.addMessageObserver(this);
}

PopupMenu::~PopupMenu() {
	window.removeMessageObserver(this);
	DestroyMenu(menuHandle);
}

void PopupMenu::addItem(wstring label, function<void()> action) {
	UINT_PTR id = SequentialFactory<UINT_PTR>::next();

	AppendMenu(menuHandle, MF_STRING, id, label.c_str());
	itemActions[id] = action;
}

void PopupMenu::show() {
	// without this, the menu would not disappear after clicking some other window (or the taskbar)
	SetForegroundWindow(window.getHandle());

	POINT pos;
	GetCursorPos(&pos);

	TrackPopupMenu(menuHandle, TPM_RIGHTBUTTON, pos.x, pos.y, 0, window.getHandle(), NULL);
}

void PopupMenu::onMessage(const Message& msg) {
	if (msg.msg == WM_COMMAND) {
		std::map<UINT_PTR, std::function<void()> >::iterator it = itemActions.find(LOWORD(msg.wParam));

		if (it != itemActions.end())
			it->second();
	}
}