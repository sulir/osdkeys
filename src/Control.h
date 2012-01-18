#pragma once
#include "Message.h"
#include "GuiElement.h"
#include "Window.h"
#include "Color.h"
#include "Area.h"
#include "Font.h"
#include <string>
#include <windows.h>

/**
 * GUI control - child window in WinAPI terminology.
 */

class Control : public GuiElement, public MessageObserver {
public:
	Control(std::wstring type, Window& parent, const Area& area);
	virtual ~Control() = 0;
	virtual void setColor(Color color);
	virtual void setFont(const Font& font);
	void onMessage(const Message& msg);
protected:
	Window& parent;
private:
	Color color;
};