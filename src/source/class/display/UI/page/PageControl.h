#ifndef SOURCE_CLASS_DISPLAY_UI_PAGE_PAGECONTROL_H_
#define SOURCE_CLASS_DISPLAY_UI_PAGE_PAGECONTROL_H_

#include "class/display/UI/UIObject.h"
namespace Input{
class Signal;
}


namespace UI {

class PageControl: public UIObject {
public:
	PageControl();
	virtual ~PageControl();
	void initialize(std::string receiver_name);

	virtual UIObject* create_UIObject(){
		return new PageControl();
	}
	virtual std::string get_type()const{
		return "PageControl";
	}
	void prev_page();
	void next_page();
	void switch_page(std::string name);
protected:
	virtual void Parse_UIScript(std::istream &is,std::string &line);
	virtual void Parse_UIScript(std::ostream &os);
	virtual void update();


	void handle_signal(Input::Signal* signal);
	unsigned cur_page;

};

} /* namespace UI */

#endif /* SOURCE_CLASS_DISPLAY_UI_PAGE_PAGECONTROL_H_ */
