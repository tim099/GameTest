#ifndef SOURCE_CLASS_DISPLAY_UI_UI_H_
#define SOURCE_CLASS_DISPLAY_UI_UI_H_
#include <vector>
#include <glm/glm.hpp>
#include "class/display/UI/UIObject.h"
#include "class/tim/parser/Parser.h"
class Draw;
namespace UI {
	class UIObjectCreator;
}

namespace UI {

class UI : public UIObject,public Tim::Parser{
	static UI *cur_UI;
public:
	UI();
	virtual ~UI();

	virtual UIObject* create_UIObject();
	virtual std::string get_type_name()const{
		return "UI";
	}

	static UI* get_cur_UI();


	UIObjectCreator* creator;
protected:
	virtual inline std::string Script_name()const{
		return "#LOAD_UI_SCRIPT";
	}
	virtual void Parse_Script(std::istream &is,std::string &line);
	virtual void Parse_Header(std::istream &is,std::string &line);
	virtual void Parse_Script(std::ostream &os);
	virtual void Parse_Header(std::ostream &os);

	virtual void start_draw(Draw* draw);
	virtual void update();


};

} /* namespace UI */

#endif /* SOURCE_CLASS_DISPLAY_UI_UI_H_ */
