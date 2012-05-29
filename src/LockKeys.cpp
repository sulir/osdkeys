#include "LockKeys.h"
#include "Color.h"
#include "Timer.h"

using namespace std;

LockKeys::LockKeys(Window& window, Label& topLabel, Label& bottomLabel, Timer* hideTimer)
: hideTimer(hideTimer) {
	capsLock = new HotKey(window, VK_CAPITAL, [&] {
		updateLabels(window, topLabel, bottomLabel);
	});

	numLock = new HotKey(window, VK_NUMLOCK, [&] {
		updateLabels(window, bottomLabel, topLabel);
	});
}

LockKeys::~LockKeys() {
	delete hideTimer;
	delete capsLock;
	delete numLock;
}

void LockKeys::updateLabels(Window& window, Label& capsLockLabel, Label& numLockLabel) {
	hideTimer->stop();

	updateLabel(capsLockLabel, VK_CAPITAL, L"CapsLock");
	updateLabel(numLockLabel, VK_NUMLOCK, L"NumLock");

	window.show();
	hideTimer->start();
}

void LockKeys::updateLabel(Label& label, UINT key, std::wstring name) {
	bool isOn = GetKeyState(key) & 1;

	label.setText(name + L": " + (isOn ? L"On" : L"Off"));
	label.setColor(isOn ? Color::GREEN : Color::RED);
}