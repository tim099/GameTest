#include "class/input/signal/Signal.h"

Signal::Signal(std::string _data,std::string _sent_to) {
	sent_to=_sent_to;
	data=_data;
}
Signal::~Signal() {

}
const std::string& Signal::get_sent_to()const{
	return sent_to;
}
const std::string& Signal::get_data()const{
	return data;
}
