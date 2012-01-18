#pragma once
#include "NonCopyable.h"
#include "Window.h"
#include "Label.h"
#include "PopupMenu.h"
#include "TrayIcon.h"
#include "LockKeys.h"

/**
 * OSDKeys application.
 */

class OSDKeys : NonCopyable {
public:
	OSDKeys() : mainWindow(NULL), topLabel(NULL), bottomLabel(NULL) {}
	void start();
	void stop();
private:
	Window* mainWindow;
	Label* topLabel;
	const Font* topLabelFont;
	Label* bottomLabel;
	const Font* bottomLabelFont;
	TrayIcon* trayIcon;
	PopupMenu* trayMenu;
	LockKeys* lockKeys;
};