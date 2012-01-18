#include "OneInstance.h"

OneInstance::OneInstance(std::wstring guid) {
	mutex = CreateMutex(NULL, false, guid.c_str());

	mutexExists = (GetLastError() == ERROR_ALREADY_EXISTS);
}

OneInstance::~OneInstance() {
	if (mutex)
		CloseHandle(mutex);
}

bool OneInstance::alreadyExists() {
	return mutexExists;
}