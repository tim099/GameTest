#ifndef SOURCE_CLASS_DISPLAY_UI_BUTTON_PICTUREBUTTON_PICTUREBUTTON_H_
#define SOURCE_CLASS_DISPLAY_UI_BUTTON_PICTUREBUTTON_PICTUREBUTTON_H_
#include "class/display/UI/button/Button.h"
#include <string>
class Texture;

namespace UI {

class PictureButton : public Button{
public:
	const static double auto_stringSize=0.0;
	static const float AutoHeight = 0.0f;
	/*
	 * auto height means it will determine height by texture's height
	 */
	PictureButton(glm::vec2 pos,std::string tex_path,float width,float height=AutoHeight);
	PictureButton();
	void initialize(glm::vec2 pos,std::string tex_path,float width,float height=AutoHeight);
	void initialize(std::string tex_path,float width,float height=AutoHeight);
	virtual ~PictureButton();

	virtual UIObject* create_UIObject();
	virtual std::string get_type_name()const{
		return "PictureButton";
	}

	void set_string(std::string* str,float str_size=auto_stringSize);

protected:
	virtual void Parse_Script(std::istream &is,std::string &line);
	virtual void Parse_Script(std::ostream &os);
	virtual void start_draw(Draw* draw);
	std::string* str;
	Texture* tex2D;
	std::string tex_path;
	float height;
	float str_size;
};

} /* namespace UI */

#endif /* SOURCE_CLASS_DISPLAY_UI_BUTTON_PICTUREBUTTON_PICTUREBUTTON_H_ */
