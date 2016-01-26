#ifndef SOURCE_CLASS_DISPLAY_UI_UIOBJECTCREATOR_H_
#define SOURCE_CLASS_DISPLAY_UI_UIOBJECTCREATOR_H_
#include "class/display/UI/UIObject.h"
#include <string>
#include <map>
namespace UI {

class UIObjectCreator {
public:
	UIObjectCreator();
	virtual ~UIObjectCreator();
	UIObject* create(std::string type_name);
protected:
	void push(UIObject* obj);
	void initial_creator();
	std::map<std::string,UIObject*>creator;
};

} /* namespace UI */

#endif /* SOURCE_CLASS_DISPLAY_UI_UIOBJECTCREATOR_H_ */
