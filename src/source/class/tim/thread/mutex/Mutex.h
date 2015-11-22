#ifndef MUTEX_H_
#define MUTEX_H_
#include <windows.h>
namespace Tim {

class Mutex {
public:
	Mutex();
	virtual ~Mutex();
	void wait_for_this(DWORD time=INFINITE);
	void release();
	HANDLE mutex;
};

} /* namespace Tim */

#endif /* MUTEX_H_ */
