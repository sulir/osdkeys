#pragma once
#include "Control.h"
#include "Window.h"
#include "Area.h"

/**
 * Static text-only label.
 */

class Label : public Control {
public:
	Label(Window& parent, const Area& dimensions) : Control(L"STATIC", parent, dimensions) {}
};