#include "class/tim/thread/mutex/Mutex.h"

namespace Tim {

Mutex::Mutex() {
	mutex=CreateMutex(NULL,FALSE,NULL);
}
Mutex::~Mutex() {
	CloseHandle(mutex);
}
void Mutex::wait_for_this(DWORD time){
	WaitForSingleObject(mutex,time);
}
void Mutex::release(){
	ReleaseMutex(mutex);
}
} /* namespace Tim */
