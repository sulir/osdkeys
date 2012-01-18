#pragma once
#include "NonCopyable.h"
#include <string>
#include <windows.h>

/**
 * GUI element is an overlapped or child window in WinAPI terminology.
 *
 * This is a base class for both main window and GUI controls.
 */

class GuiElement : NonCopyable {
public:
	GuiElement() {}
	virtual ~GuiElement() = 0;
	virtual void show();
	virtual void hide();
	void setText(const std::wstring text);
	HWND getHandle() const { return handle; }
protected:
	HWND handle;
};