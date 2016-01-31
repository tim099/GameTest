#ifndef SOURCE_CLASS_DISPLAY_UI_UIOBJECTCREATOR_H_
#define SOURCE_CLASS_DISPLAY_UI_UIOBJECTCREATOR_H_
#include "class/display/UI/UIObject.h"
#include "class/tim/map/MapContainer.h"
#include "class/tim/globalObject/GlobalObject.h"
#include <string>

namespace UI {

class UIObjectCreator : public Tim::GlobalObject<UIObjectCreator>{
public:
	UIObjectCreator();
	virtual ~UIObjectCreator();
	UIObject* create(std::string type_name);
protected:
	void push(UIObject* obj);
	void initial_creator();
	Tim::MapContainer<std::string,UIObject>creator;
};

} /* namespace UI */

#endif /* SOURCE_CLASS_DISPLAY_UI_UIOBJECTCREATOR_H_ */
