#include "GuiElement.h"

using namespace std;

GuiElement::~GuiElement() {}

void GuiElement::show() {
	ShowWindow(handle, SW_SHOWNA);
	UpdateWindow(handle);
}

void GuiElement::hide() {
	ShowWindow(handle, SW_HIDE);
}

void GuiElement::setText(const wstring text) {
	SetWindowText(handle, text.c_str());
}