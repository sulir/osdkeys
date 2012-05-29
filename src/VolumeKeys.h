#pragma once
#include "NonCopyable.h"
#include "HotKey.h"
#include "Window.h"
#include "Label.h"
#include "Timer.h"
#include "MasterVolume.h"
#include <memory>

/**
 * Class for showing Volume +/- and Mute key events.
 */

class VolumeKeys : NonCopyable {
public:
	VolumeKeys(Window& window, Label& topLabel, Label& bottomLabel, Timer* hideTimer);
	~VolumeKeys();
private:
	void updateLabels(Window& window, Label& volumeLabel, Label& muteLabel);
	void udpateVolumeLabel(Label& label);
	void udpateMuteLabel(Label& label);
	VolumeKeys(const VolumeKeys&);
	VolumeKeys& operator=(const VolumeKeys&);
	Timer* hideTimer;
	std::auto_ptr<MasterVolume> volume;
	HotKey* volumeDown;
	HotKey* volumeUp;
	HotKey* volumeMute;
};