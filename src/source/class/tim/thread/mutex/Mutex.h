#ifndef MUTEX_H_
#define MUTEX_H_
#include <windows.h>
namespace Tim {

class Mutex {
public:
	Mutex();
	virtual ~Mutex();
	inline void wait_for_this(DWORD time=INFINITE){
		WaitForSingleObject(mutex,time);
	}
	inline void release(){
		ReleaseMutex(mutex);
	}
	HANDLE mutex;
};

} /* namespace Tim */

#endif /* MUTEX_H_ */
