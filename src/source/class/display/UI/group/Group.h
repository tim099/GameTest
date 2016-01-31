#ifndef SOURCE_CLASS_DISPLAY_UI_GROUP_GROUP_H_
#define SOURCE_CLASS_DISPLAY_UI_GROUP_GROUP_H_

#include "class/display/UI/UIObject.h"

namespace UI {

class Group: public UIObject {
public:
	Group();
	virtual ~Group();
	virtual std::string get_type()const{
		return "Group";
	}
protected:

};

} /* namespace UI */

#endif /* SOURCE_CLASS_DISPLAY_UI_GROUP_GROUP_H_ */
