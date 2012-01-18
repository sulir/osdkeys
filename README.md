OSDKeys - Volume & Lock-keys OSD
================================

OSDKeys is a small system utility for Windows which runs in the background. It displays volume information each time a volume-control multimedia key (+, -, Mute) is pressed and CapsLock / NumLock status after pressing one of the lock keys.

Features
--------

* Volume information
 * percentage
 * muted / unmuted status
* Lock keys status
 * CapsLock
 * NumLock
 * states are also distinguished by color (green / red)
* Tray icon
 * to exit the application :-)
* Windows XP, Vista and Windows 7 supported

Compilation
-----------
The project is tested to compile with:

* MS Visual C++ 2010 Express
* GCC 4.7, both x86 and x64

Currently, the GCC build does not function properly on Windows Vista / 7 because of a COM-related error. The MSVC build works fine.