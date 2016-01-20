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
	PictureButton(glm::vec2 pos,Texture* tex2D,double width,double height=AutoHeight);
	virtual ~PictureButton();
	virtual void start_draw(Draw* draw);
	void set_string(std::string* str,double str_size=auto_stringSize);
protected:
	std::string* str;
	Texture* tex2D;
	double height;
	double str_size;
};

} /* namespace UI */

#endif /* SOURCE_CLASS_DISPLAY_UI_BUTTON_PICTUREBUTTON_PICTUREBUTTON_H_ */
