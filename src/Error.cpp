#include "Error.h"
#include <windows.h>

using namespace std;

void ErrorMessage::show() const {
	wchar_t errorNumber[21];
	wsprintf(errorNumber, L"%lu", GetLastError());
	
	const wstring message = msg + L" Error Code: " + errorNumber;
	MessageBox(NULL, message.c_str(), L"Error", MB_ICONEXCLAMATION | MB_OK);
	
	if (fatal)
		ExitProcess(1);
}