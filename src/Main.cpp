#include "OSDKeys.h"
#include "Error.h"
#include "OneInstance.h"
#include <memory>
#include <windows.h>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	OneInstance oneInstance(L"{E9CDDF6D-5BEA-4dd5-98DA-AD3388EED343}");

	if (oneInstance.alreadyExists()) {
		ErrorMessage(L"Another copy of OSDKeys is already running.", true).show();
	}

	OSDKeys osdKeys;

	try {
		osdKeys.start();
	} catch(WindowsException &ex) {
		ErrorMessage(ex.wwhat(), true).show();
	}

	MSG msg = {};

	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	osdKeys.stop();
	return msg.wParam;
}