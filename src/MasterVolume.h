#pragma once
#include <windows.h>
#include <mmdeviceapi.h>
#include <endpointvolume.h>

/**
 * Class for reading master volume level and mute status.
 *
 * Supports both old Win2K and new WinVista audio API.
 */

class MasterVolume {
public:
	MasterVolume();
	~MasterVolume();
	int getLevel() const;
	bool isMuted() const;
private:
	class MasterVolumeInterface {
	public:
		virtual int getLevel() = 0;
		virtual bool isMuted() = 0;
		virtual ~MasterVolumeInterface() {}
	};

	class Implementation2K : public MasterVolumeInterface {
	public:
		int getLevel();
		bool isMuted();
	private:
		MIXERLINE getMixerLine(HMIXER mixer);
		MIXERCONTROL getMixerControl(HMIXER mixer, MIXERLINE line, DWORD controlType);
		template<class T> T getMixerControlDetails(DWORD controlType);
	};

	class ImplementationVista : public MasterVolumeInterface {
	public:
		int getLevel();
		bool isMuted();
	private:
		IMMDevice* getMMDevice();
		IAudioEndpointVolume* getAudioEndpointVolume();
	};

	bool isVistaOrLater();
	MasterVolumeInterface* implementation;
};