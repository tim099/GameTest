#ifndef SOURCE_CLASS_DISPLAY_UI_STRING_UISTRING_H_
#define SOURCE_CLASS_DISPLAY_UI_STRING_UISTRING_H_

#include "class/display/UI/UIObject.h"

namespace UI {

class UIString: public UIObject {
public:
	UIString();
	void initialize(std::string* str,float font_size);
	virtual ~UIString();

	virtual UIObject* create_UIObject();
	virtual std::string get_type()const{
		return "UIString";
	}
	void set_string(std::string str);
	std::string get_string();
	//if input_mode==true then this string will get the keyboard input
	bool input_mode;
protected:
	virtual void Parse_UIScript(std::istream &is,std::string &line);
	virtual void Parse_UIScript(std::ostream &os);
	virtual void update();
	virtual void start_draw(Draw* draw);
	std::string* str;
	float font_size;
};

} /* namespace UI */

#endif /* SOURCE_CLASS_DISPLAY_UI_STRING_UISTRING_H_ */
