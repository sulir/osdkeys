#include "OSDKeys.h"
#include "Area.h"
#include "Font.h"
#include <windows.h>

void OSDKeys::start() {
	mainWindow = new Window(L"OSDKeys", Area(10, 10, 250, 120));

	topLabel = new Label(*mainWindow, Area(10, 10, 230, 50));
	bottomLabel = new Label(*mainWindow, Area(10, 70, 230, 40));

	topLabelFont = new Font(L"Arial", 30, true);
	topLabel->setFont(*topLabelFont);

	bottomLabelFont = new Font(L"Arial", 20, true);
	bottomLabel->setFont(*bottomLabelFont);

	trayIcon = new TrayIcon(*mainWindow, L"OSDKeys");
	trayMenu = new PopupMenu(*mainWindow);
	trayMenu->addItem(L"Exit", [] {
		PostQuitMessage(0);
	});
	trayIcon->setPopupMenu(trayMenu);

	lockKeys = new LockKeys(*mainWindow, *topLabel, *bottomLabel);
}

void OSDKeys::stop() {
	delete lockKeys;
	delete trayMenu;
	delete trayIcon;

	delete topLabel;
	delete topLabelFont;
	delete bottomLabel;
	delete bottomLabelFont;
	delete mainWindow;
}