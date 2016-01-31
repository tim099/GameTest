#ifndef SOURCE_CLASS_DISPLAY_UI_GROUP_SORTGROUP_H_
#define SOURCE_CLASS_DISPLAY_UI_GROUP_SORTGROUP_H_

#include "class/display/UI/group/Group.h"

namespace UI {

class SortGroup: public Group {
public:
	SortGroup();
	virtual ~SortGroup();
	virtual UIObject* create_UIObject(){
		return new SortGroup();
	}
	virtual std::string get_type()const{
		return "SortGroup";
	}
	/*
	 * set the interval between each child
	 */
	void set_interval(glm::vec2 interval);
protected:
	virtual void Parse_UIScript(std::istream &is,std::string &line);
	virtual void Parse_UIScript(std::ostream &os);
	virtual void update();

	void sort();
	glm::vec2 interval;
};

} /* namespace UI */

#endif /* SOURCE_CLASS_DISPLAY_UI_GROUP_SORTGROUP_H_ */
