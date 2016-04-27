#ifndef SOURCE_CLASS_INPUT_SIGNAL_RECEIVER_H_
#define SOURCE_CLASS_INPUT_SIGNAL_RECEIVER_H_
#include <queue>
#include <string>
#include "class/input/signal/Signal.h"
namespace Input{
class Receiver {
public:
	Receiver(std::string name);
	virtual ~Receiver();
	const std::string& get_name();
	void push_signal(Signal* signal);
	Signal *get_signal();
protected:
	std::string name;
	std::queue<Signal*>signal_q;
};
}
#endif /* SOURCE_CLASS_INPUT_SIGNAL_RECEIVER_H_ */
