#pragma once
#include "Message.h"
#include "Window.h"
#include "Timer.h"
#include <functional>
#include <windows.h>

/**
 * Class to enable registration of a system-wide hot key.
 * 
 * If two instances specify the same key, the behavior is undefined.
 */

class HotKey : public MessageObserver {
public:
	HotKey(Window& window, UINT key, std::function<void()> action, bool enabled = true);
	~HotKey();
	void enable();
	void disable();
	void onMessage(const Message& msg);
private:
	void registerKey();
	void unregisterKey();
	void simulateKeyPress();
	Window& window;
	UINT key;
	std::function<void()> action;
	bool enabled;
	Timer* actionTimer;
};