#include "class/display/UI/page/PageControl.h"
#include "class/input/signal/Receiver.h"

namespace UI {

PageControl::PageControl() {
	cur_page = 0;
}
void PageControl::initialize(std::string receiver_name) {
	set_receiver(receiver_name);
}
PageControl::~PageControl() {

}
void PageControl::Parse_UIScript(std::istream &is, std::string &line) {

}
void PageControl::Parse_UIScript(std::ostream &os) {

}
void PageControl::prev_page() {
	if (cur_page > 0) {
		cur_page--;
	}
}
void PageControl::next_page() {
	if (cur_page < childs.size() - 1) {
		cur_page++;
	}
}
void PageControl::switch_page(std::string name) {
	bool find = false;
	for (unsigned i = 0; i < childs.size(); i++) {
		if (childs.at(i)->get_name() == name) {
			cur_page = i;
			find = true;
		}
	}
	if (!find) {
		std::cerr << "PageControl::switch_page fail,unknown page name"
				<< std::endl;
		return;
	}
}
void PageControl::handle_signal(Input::Signal* signal) {
	if (signal->get_data() == "prev_page") {
		prev_page();
	} else if (signal->get_data() == "next_page") {
		next_page();
	} else {
		switch_page(signal->get_data());
	}
}
void PageControl::update() {
	if (receiver) {
		Input::Signal *sig;
		while ((sig = receiver->get_signal())) {
			handle_signal(sig);
		}
	}
	for (unsigned i = 0; i < childs.size(); i++) {
		if (i == cur_page) {
			childs.at(i)->hide = false;
		} else {
			childs.at(i)->hide = true;
		}
	}
}
} /* namespace UI */
