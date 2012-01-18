#pragma once
#include <string>

/**
 * Fatal or non-fatal error message box.
 */

class ErrorMessage {
public:
	ErrorMessage(const std::wstring msg, bool fatal = false) : msg(msg), fatal(fatal) {}
	void show() const;
private:
	const std::wstring msg;
	const bool fatal;
};

/**
 * Exception representing a failure of a WinAPI call.
 */

class WindowsException : public std::exception {
private:
	const std::wstring msg;
public:
	WindowsException(const std::wstring& msg = L"") : msg(msg) {}
	virtual ~WindowsException() throw() {}
	virtual std::wstring wwhat() const { return msg; }
};