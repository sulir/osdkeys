#pragma once
#include <windows.h>

/**
 * WinAPI message (hWnd is excluded).
 */

struct Message {
	Message(UINT msg, WPARAM wParam, LPARAM lParam) : msg(msg), wParam(wParam), lParam(lParam) {}
	const UINT msg;
	const WPARAM wParam;
	const LPARAM lParam;
};

/**
 * Interface to be implemented by all classes which would wish to recieve window messages.
 */

class MessageObserver {
public:
	virtual ~MessageObserver() {}
	virtual void onMessage(const Message& msg) = 0;
};