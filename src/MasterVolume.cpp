#include "MasterVolume.h"
#include <climits>

MasterVolume::MasterVolume() {
	if (isVistaOrLater())
		implementation = new ImplementationVista();
	else
		implementation = new Implementation2K();
}

MasterVolume::~MasterVolume() {
	delete implementation;
}

int MasterVolume::getLevel() const {
	return implementation->getLevel();
}

bool MasterVolume::isMuted() const {
	return implementation->isMuted();
}

bool MasterVolume::isVistaOrLater() {
	OSVERSIONINFO version = {};
	version.dwOSVersionInfoSize = sizeof version;
	GetVersionEx(&version);

	return (version.dwMajorVersion >= 6);
}

int MasterVolume::Implementation2K::getLevel() {
	MIXERCONTROLDETAILS_UNSIGNED result = getMixerControlDetails<MIXERCONTROLDETAILS_UNSIGNED>(MIXERCONTROL_CONTROLTYPE_VOLUME);

	double percent = result.dwValue * 100 / USHRT_MAX;
	return static_cast<int>(percent + 0.5); // round
}

bool MasterVolume::Implementation2K::isMuted() {
	MIXERCONTROLDETAILS_BOOLEAN result = getMixerControlDetails<MIXERCONTROLDETAILS_BOOLEAN>(MIXERCONTROL_CONTROLTYPE_MUTE);

	return (result.fValue == 1); // disable MSVC warning
}

MIXERLINE MasterVolume::Implementation2K::getMixerLine(HMIXER mixer) {
	MIXERLINE line = {};

	line.cbStruct = sizeof line;
	line.dwComponentType = MIXERLINE_COMPONENTTYPE_DST_SPEAKERS;

	mixerGetLineInfo(reinterpret_cast<HMIXEROBJ>(mixer), &line, MIXER_GETLINEINFOF_COMPONENTTYPE);

	return line; // let the compiler optimize returning this large struct by value
}

MIXERCONTROL MasterVolume::Implementation2K::getMixerControl(HMIXER mixer, MIXERLINE line, DWORD controlType) {
	MIXERLINECONTROLS controls = {};
	MIXERCONTROL ctrl = {};

	controls.cbStruct = sizeof controls;
	controls.dwLineID = line.dwLineID;
	controls.dwControlType = controlType;
	controls.cControls = 1;
	controls.cbmxctrl = sizeof ctrl;
	controls.pamxctrl = &ctrl;

	mixerGetLineControls(reinterpret_cast<HMIXEROBJ>(mixer), &controls, MIXER_GETLINECONTROLSF_ONEBYTYPE);

	return ctrl;
}

template<class T> T MasterVolume::Implementation2K::getMixerControlDetails(DWORD controlType) {
	HMIXER mixer;
	mixerOpen(&mixer, 0, 0, 0, 0);

	MIXERLINE line = getMixerLine(mixer);
	MIXERCONTROL control = getMixerControl(mixer, line, controlType);

	MIXERCONTROLDETAILS details = {};
	T result;

	details.cbStruct = sizeof details;
	details.dwControlID = control.dwControlID;
	details.cChannels = 1;
	details.cbDetails = sizeof result;
	details.paDetails = &result;
	mixerGetControlDetails(reinterpret_cast<HMIXEROBJ>(mixer), &details, MIXER_GETCONTROLDETAILSF_VALUE);

	mixerClose(mixer);

	return result;
}

int MasterVolume::ImplementationVista::getLevel() {
	CoInitialize(NULL);

	IAudioEndpointVolume* endVol = getAudioEndpointVolume();
	float volume;
	
	endVol->GetMasterVolumeLevelScalar(&volume);
	endVol->Release();
	
	CoUninitialize();

	double percent = 100 * volume;
	return static_cast<int>(percent + 0.5); // round
}

bool MasterVolume::ImplementationVista::isMuted() {
	CoInitialize(NULL);

	IAudioEndpointVolume* endVol = getAudioEndpointVolume();
	BOOL muted;
	
	endVol->GetMute(&muted);
	endVol->Release();
	
	CoUninitialize();

	return (muted == 1);
}

IMMDevice* MasterVolume::ImplementationVista::getMMDevice() {
	CLSID clsidMMDeviceEnumerator = __uuidof(MMDeviceEnumerator);
	IID iidIMMDeviceEnumerator = __uuidof(IMMDeviceEnumerator);
	
	IMMDeviceEnumerator* deviceEnum;
	CoCreateInstance(clsidMMDeviceEnumerator, NULL, CLSCTX_INPROC_SERVER,
		iidIMMDeviceEnumerator, (void**)&deviceEnum);

	IMMDevice* device;
	deviceEnum->GetDefaultAudioEndpoint(eRender, eConsole, &device);
	deviceEnum->Release();

	return device;
}

IAudioEndpointVolume* MasterVolume::ImplementationVista::getAudioEndpointVolume() {
	IMMDevice* device = getMMDevice();

	IAudioEndpointVolume* endVol;
	
	// MinGW misses IID_IAudioEndpointVolume, __uuidof(IAudioEndpointVolume) causes linker error.
	// This IID is taken from a Windows 7 machine by debugging the MSVC build:
	LPOLESTR iidStr = const_cast<LPOLESTR>(L"{5CDF2C82-841E-4546-9722-0CF74078229A}");
	IID iidIAudioEndpointVolume;
	IIDFromString(iidStr, &iidIAudioEndpointVolume);
	
	device->Activate(iidIAudioEndpointVolume, CLSCTX_INPROC_SERVER, NULL, (void**)&endVol);
	device->Release();

	return endVol;
}