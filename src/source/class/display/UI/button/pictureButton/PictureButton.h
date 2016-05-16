#ifndef SOURCE_CLASS_DISPLAY_UI_BUTTON_PICTUREBUTTON_PICTUREBUTTON_H_
#define SOURCE_CLASS_DISPLAY_UI_BUTTON_PICTUREBUTTON_PICTUREBUTTON_H_
#include "class/display/UI/button/Button.h"
#include <string>
namespace Display{
class Texture;
}
namespace UI {

class PictureButton : public Button{
public:
	const static float auto_Size=0.0f;
	static const float AutoHeight = 0.0f;
	/*
	 * auto height means it will determine height by texture's height
	 */
	PictureButton(math::vec2<float> pos,std::string tex_path,float width,float height=AutoHeight);
	PictureButton();
	virtual void init(math::vec2<float>,std::string tex_path,float width,float height=AutoHeight);

	void set_texture(std::string tex_path,float width,float height=AutoHeight);

	//using pre loaded internal data to set_texture
	void set_texture();
	void Parse_texture(std::istream &is,std::string &line);
	void Parse_texture(std::ostream &os);

	virtual ~PictureButton();

	virtual UIObject* create_UIObject();
	virtual UIObject* copy_UIObject();
	virtual std::string get_type()const{
		return "PictureButton";
	}

	void set_string(std::string* str,float font_size=auto_Size);

protected:
	virtual void Parse_UIScript(std::istream &is,std::string &line);
	virtual void Parse_UIScript(std::ostream &os);
	virtual void start_draw(Display::Draw* draw);
	std::string* str;
	Display::Texture* tex2D;
	std::string tex_path;
	float height;
	float font_size;
};

} /* namespace UI */

#endif /* SOURCE_CLASS_DISPLAY_UI_BUTTON_PICTUREBUTTON_PICTUREBUTTON_H_ */
