#include "class/tim/thread/mutex/Mutex.h"

namespace Tim {

Mutex::Mutex() {
	mutex=CreateMutex(NULL,FALSE,NULL);
}
Mutex::~Mutex() {
	CloseHandle(mutex);
}
} /* namespace Tim */
