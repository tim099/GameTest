/*
 * ToggleButton.cpp
 *
 *  Created on: 2016¦~5¤ë16¤é
 *      Author: LukeWu
 */

#include "class/display/UI/button/pictureButton/ToggleButton.h"

namespace UI {

ToggleButton::ToggleButton(math::vec2<float> pos,std::string tex_path,float width,float height)
	:PictureButton(pos, tex_path, width, height)
{
	// TODO Auto-generated constructor stub
}

ToggleButton::ToggleButton()
	:PictureButton()
{

}

ToggleButton::~ToggleButton() {
	// TODO Auto-generated destructor stub
}

void ToggleButton::selected(){
	for (unsigned int i=0; i<childs.size(); i++) {
		childs[i]->hide = !childs[i]->hide;
	}
}

} /* namespace AOC */
