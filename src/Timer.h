#pragma once
#include "Window.h"
#include "Message.h"
#include <functional>
#include <windows.h>

/**
 * One-shot alarm timer.
 */

class Timer : public MessageObserver {
public:
	Timer(Window& window, UINT milliseconds = 1000U, std::function<void()> elapseAction = NULL);
	void setMilliseconds(UINT milliseconds) { this->milliseconds = milliseconds; }
	void setElapseAction(std::function<void()> action) { this->elapseAction = action; }
	void start();
	void stop();
private:
	void onMessage(const Message& msg);
	Window& window;
	unsigned int milliseconds;
	std::function<void()> elapseAction;
	bool running;
	UINT_PTR eventID;
};