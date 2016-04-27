#include "class/input/signal/Receiver.h"
#include <iostream>
namespace Input{
Receiver::Receiver(std::string _name) {
	name=_name;
}
Receiver::~Receiver() {

}
const std::string& Receiver::get_name(){
	return name;
}
void Receiver::push_signal(Signal* signal){
	signal_q.push(signal);
}
Signal *Receiver::get_signal(){
	if(signal_q.empty()){
		return 0;
	}

	Signal *s=signal_q.front();
	signal_q.pop();//don't delete the signal!!
	return s;
}
}
