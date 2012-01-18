#include "Timer.h"
#include "SequentialFactory.h"

Timer::Timer(Window& window, UINT milliseconds, std::function<void()> elapseAction)
: window(window), milliseconds(milliseconds), elapseAction(elapseAction), running(false), eventID(0) {
	eventID = SequentialFactory<UINT_PTR, 1U>::next();
}

void Timer::start() {
	if (!running) {
		running = true;
		window.addMessageObserver(this);

		SetTimer(window.getHandle(), eventID, milliseconds, NULL);
	}
}

void Timer::stop() {
	if (running) {
		KillTimer(window.getHandle(), eventID);

		running = false;
		window.removeMessageObserver(this);
	}
}

void Timer::onMessage(const Message& msg) {
	if (msg.msg == WM_TIMER && msg.wParam == eventID) {
		window.removeMessageObserver(this);
		running = false;

		if (elapseAction != NULL)
			elapseAction();
	}
}