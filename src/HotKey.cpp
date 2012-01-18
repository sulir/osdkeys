#include "HotKey.h"
#include "Timer.h"

HotKey::HotKey(Window& window, UINT key, std::function<void()> action, bool enabled)
: window(window), key(key), action(action), enabled(enabled) {
	if (enabled)
		registerKey();

	actionTimer = new Timer(window, 1, action);

	window.addMessageObserver(this);
}

HotKey::~HotKey() {
	window.removeMessageObserver(this);
	disable();
	delete actionTimer;
}

void HotKey::enable() {
	if (!enabled) {
		registerKey();
		enabled = true;
	}
}

void HotKey::disable() {
	if (enabled) {
		unregisterKey();
		enabled = false;
	}
}

void HotKey::onMessage(const Message& msg) {
	if (msg.msg == WM_HOTKEY && msg.wParam == key) {
		unregisterKey();
		simulateKeyPress();
		registerKey();

		// The action is called after a short pause.
		// This increases the probability that the default (system) action has already been executed
		// (after simulating the key press).
		actionTimer->start();
	}
}

void HotKey::registerKey() {
	// IDs are chosen the same as virtual key codes
	RegisterHotKey(window.getHandle(), key, 0, key);
}

void HotKey::unregisterKey() {
	UnregisterHotKey(window.getHandle(), key);
}

void HotKey::simulateKeyPress() {
	KEYBDINPUT keybdDown = {};
	keybdDown.wVk = key;
	keybdDown.dwFlags = KEYEVENTF_EXTENDEDKEY;

	KEYBDINPUT keybdUp = {};
	keybdUp.wVk = key;
	keybdUp.dwFlags = KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP;

	INPUT input[2];

	input[0].type = INPUT_KEYBOARD;
	input[0].ki = keybdDown;

	input[1].type = INPUT_KEYBOARD;
	input[1].ki = keybdUp;	

	// the last parameter must be the size of one structure, not an entire array
	SendInput(2, input, sizeof(INPUT));
}