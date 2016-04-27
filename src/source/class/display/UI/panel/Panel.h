#ifndef SOURCE_CLASS_DISPLAY_UI_PANEL_PANEL_H_
#define SOURCE_CLASS_DISPLAY_UI_PANEL_PANEL_H_
#include "class/display/UI/UIObject.h"
#include <glm/vec2.hpp>
#include "class/input/mouse/selectable/rectangle/SelectableRec.h"
namespace Display{
class Texture;
}
namespace UI {

class Panel: public UIObject {
public:
	static const float AutoHeight = 0.0f;
	Panel();
	Panel(glm::vec2 pos,std::string tex_path,float width,float height=AutoHeight);
	void init(glm::vec2 pos,std::string tex_path,float width,float height=AutoHeight);
	void set_texture(std::string tex_path,float width,float height=AutoHeight);
	virtual ~Panel();

	virtual UIObject* create_UIObject();
	virtual std::string get_type()const{
		return "Panel";
	}

protected:
	virtual void Parse_UIScript(std::istream &is,std::string &line);
	virtual void Parse_UIScript(std::ostream &os);
	virtual void update();
	virtual void start_draw(Display::Draw* draw);
//========================================================

	//provide update for inherit class from Panel
	virtual void update_panel();

	std::string tex_path;
	Display::Texture* tex2D;
	float height;
};

} /* namespace UI */

#endif /* SOURCE_CLASS_DISPLAY_UI_PANEL_PANEL_H_ */
