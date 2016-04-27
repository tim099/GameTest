#ifndef SOURCE_CLASS_DISPLAY_UI_UI_H_
#define SOURCE_CLASS_DISPLAY_UI_UI_H_
#include <vector>
#include <glm/glm.hpp>
#include "class/display/UI/UIObject.h"
#include "class/tim/parser/Parser.h"
namespace Display{
class Draw;
}

namespace UI {


class UI : public UIObject,public Tim::Parser{
public:
	UI();
	UI(std::string script_path);
	virtual ~UI();

	virtual UIObject* create_UIObject(){
		return new UI();
	}
	virtual std::string get_type()const{
		return "UI";
	}

protected:
	virtual bool save_child()const{
		return false;
	}
	//=================UIObject==========================
	virtual void Parse_UIScript(std::istream &is,std::string &line);
	virtual void Parse_UIScript(std::ostream &os);
	//=================Tim::Parser=======================
	virtual inline std::string Script_name()const{
		return "#LOAD_UI_SCRIPT";
	}
	virtual void Parse_Script(std::istream &is,std::string &line);
	virtual void Parse_Header(std::istream &is,std::string &line);
	virtual void Parse_Script(std::ostream &os);
	virtual void Parse_Header(std::ostream &os);

	virtual void start_draw(Display::Draw* draw);
	virtual void update();

	std::string script_path;
};

} /* namespace UI */

#endif /* SOURCE_CLASS_DISPLAY_UI_UI_H_ */
