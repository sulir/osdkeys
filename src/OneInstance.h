#pragma once
#include <string>
#include <windows.h>

/**
 * Class to detect whether another instance of this application is alredy running.
 */

class OneInstance {
public:
	OneInstance(std::wstring guid);
	~OneInstance();
	bool alreadyExists();
private:
	HANDLE mutex;
	bool mutexExists;
};