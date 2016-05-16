/*
 * ToggleButton.cpp
 *
 *  Created on: 2016¦~5¤ë16¤é
 *      Author: LukeWu
 */

#include <iostream>
#include "class/display/UI/button/pictureButton/ToggleButton.h"

namespace UI {

ToggleButton::ToggleButton(math::vec2<float> pos,std::string tex_path,float _width,float _height)
	:PictureButton(pos, tex_path, _width, _height)
{
	hide = true;
	height= 10;
	std::cout<<"construct toggle button"<<std::endl;

	// TODO Auto-generated constructor stub
}

ToggleButton::ToggleButton()
	:PictureButton()
{

}

ToggleButton::~ToggleButton() {
	// TODO Auto-generated destructor stub
}

void ToggleButton::selected(Input::Mouse* mou){
	std::cout<<"toggle"<<std::endl;
	for (unsigned int i=0; i<childs.size(); i++) {
		childs[i]->hide = !(childs[i]->hide);
	}
}

UIObject* ToggleButton::create_UIObject(){
	return new ToggleButton();
}

} /* namespace AOC */
