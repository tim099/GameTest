#include "class/input/signal/Signal.h"
#include "class/input/signal/Receiver.h"
#include "class/input/Input.h"
Signal::Signal(std::string _data,std::string _sent_to) {
	sent_to=_sent_to;
	data=_data;
	receiver=0;
}
Signal::Signal(std::string _data,Receiver* _receiver){
	data=_data;
	receiver=_receiver;
}
Signal::~Signal() {

}
const std::string& Signal::get_sent_to()const{
	return sent_to;
}
const std::string& Signal::get_data()const{
	return data;
}
void Signal::sent(){
	if(receiver){
		receiver->push_signal(this);
	}else{
		Input::get_cur_input()->sent_signal(this);
	}
}
