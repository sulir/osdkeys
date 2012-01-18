#include "VolumeKeys.h"
#include "Color.h"
#include <string>
#include <functional>

using namespace std;

VolumeKeys::VolumeKeys(Window& window, Label& topLabel, Label& bottomLabel) : volume(new MasterVolume()) {
	hideTimer = new Timer(window, 2000U, [&] {
		window.hide();
	});

	function<void()> onVolumeChange = [&] {
		updateLabels(window, topLabel, bottomLabel);
	};

	volumeDown = new HotKey(window, VK_VOLUME_DOWN, onVolumeChange);
	volumeUp = new HotKey(window, VK_VOLUME_UP, onVolumeChange);

	volumeMute = new HotKey(window, VK_VOLUME_MUTE, [&] {
		updateLabels(window, bottomLabel, topLabel);
	});
}

VolumeKeys::~VolumeKeys() {
	delete hideTimer;
	delete volumeDown;
	delete volumeUp;
	delete volumeMute;
}

void VolumeKeys::updateLabels(Window& window, Label& volumeLabel, Label& muteLabel) {
	hideTimer->stop();

	this->udpateVolumeLabel(volumeLabel);
	this->udpateMuteLabel(muteLabel);

	window.show();
	hideTimer->start();
}

void VolumeKeys::udpateVolumeLabel(Label& label) {
	wchar_t level[21];
	wsprintf(level, L"%d", volume->getLevel());

	label.setColor(Color::WHITE);
	label.setText(wstring(L"Volume: ") + level);
}

void VolumeKeys::udpateMuteLabel(Label& label) {
	bool muted = volume->isMuted();

	label.setColor(muted ? Color::RED : Color::GREEN);
	label.setText(muted ? L"Sound Muted" : L"Sound Unmuted");
}