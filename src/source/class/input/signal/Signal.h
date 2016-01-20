#ifndef SOURCE_CLASS_INPUT_SIGNAL_SIGNAL_H_
#define SOURCE_CLASS_INPUT_SIGNAL_SIGNAL_H_
#include <string>
class Signal {
public:
	Signal(std::string data,std::string sent_to="default");
	virtual ~Signal();
	const std::string& get_sent_to()const;
	const std::string& get_data()const;
protected:
	std::string sent_to;
	std::string data;
};

#endif /* SOURCE_CLASS_INPUT_SIGNAL_SIGNAL_H_ */
