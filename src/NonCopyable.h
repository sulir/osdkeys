#pragma once

/**
 * Base class which forbids the copy-constructor and the assignment operator.
 */

class NonCopyable {
protected:
	NonCopyable() {}
private:
	NonCopyable(const NonCopyable&); // disable
	NonCopyable operator=(const NonCopyable&); // disable
};