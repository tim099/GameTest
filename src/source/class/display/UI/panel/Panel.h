#ifndef SOURCE_CLASS_DISPLAY_UI_PANEL_PANEL_H_
#define SOURCE_CLASS_DISPLAY_UI_PANEL_PANEL_H_
#include "class/display/UI/UIObject.h"
#include <glm/vec2.hpp>
#include "class/input/mouse/selectable/rectangle/SelectableRec.h"
class Texture;
namespace UI {

class Panel: public UIObject {
public:
	static const float AutoHeight = 0.0f;
	Panel();
	Panel(glm::vec2 pos,std::string tex_path,float width,float height=AutoHeight);
	void initialize(glm::vec2 pos,std::string tex_path,float width,float height=AutoHeight);
	void initialize(std::string tex_path,float width,float height=AutoHeight);
	virtual ~Panel();

	virtual UIObject* create_UIObject();
	virtual std::string get_type_name()const{
		return "Panel";
	}

protected:
	virtual void Parse_Script(std::istream &is,std::string &line);
	virtual void Parse_Script(std::ostream &os);
	virtual void update();

	/*
	 * provide for inherit class from Panel
	 * updated every frame
	 */
	virtual void update_panel();
	virtual void start_draw(Draw* draw);
	std::string tex_path;
	Texture* tex2D;
	float height;
};

} /* namespace UI */

#endif /* SOURCE_CLASS_DISPLAY_UI_PANEL_PANEL_H_ */
