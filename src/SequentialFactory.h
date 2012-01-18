#pragma once
#include <windows.h>

/**
 * Produces variables of the given type, each time incremented by one.
 */

template <class T, T first = T()> class SequentialFactory {
public:
	static T next() {
		return variable++;
	}
private:
	static T variable;
};

template <class T, T first> T SequentialFactory<T, first>::variable = first;