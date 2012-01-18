#pragma once
#include "NonCopyable.h"
#include "HotKey.h"
#include "Window.h"
#include "Label.h"
#include "Timer.h"
#include <string>
#include <windows.h>

/**
 * Class for showing CapsLock and NumLock key events.
 */

class LockKeys : NonCopyable {
public:
	LockKeys(Window& window, Label& topLabel, Label& bottomLabel);
	~LockKeys();
	void registerEvents();
private:
	void updateLabels(Window& window, Label& capsLockLabel, Label& numLockLabel);
	void updateLabel(Label& label, UINT key, std::wstring name);
	Timer* hideTimer;
	HotKey* capsLock;
	HotKey* numLock;
};