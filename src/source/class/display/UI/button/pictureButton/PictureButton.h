#ifndef SOURCE_CLASS_DISPLAY_UI_BUTTON_PICTUREBUTTON_PICTUREBUTTON_H_
#define SOURCE_CLASS_DISPLAY_UI_BUTTON_PICTUREBUTTON_PICTUREBUTTON_H_
#include "class/display/UI/button/Button.h"

namespace UI {

class PictureButton : public Button{
public:
	PictureButton(Tim::RectP2D* select_range);
	virtual ~PictureButton();
};

} /* namespace UI */

#endif /* SOURCE_CLASS_DISPLAY_UI_BUTTON_PICTUREBUTTON_PICTUREBUTTON_H_ */
