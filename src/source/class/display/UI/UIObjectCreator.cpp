#include "class/display/UI/UIObjectCreator.h"
#include "class/display/UI/UI.h"

#include "class/display/UI/button/pictureButton/ToggleButton.h"
#include "class/display/UI/button/pictureButton/PictureButton.h"

#include "class/display/UI/panel/Panel.h"

#include "class/display/UI/group/SortGroup.h"

#include "class/display/UI/page/PageControl.h"
#include "class/display/UI/page/AutoPageControl.h"

#include "class/display/UI/string/UIString.h"
#include "class/display/UI/unitUI/BuildingUI.h"
#include <iostream>
namespace UI {

UIObjectCreator::UIObjectCreator() {
	initial_creator();
}
UIObjectCreator::~UIObjectCreator() {

}
UIObject* UIObjectCreator::create(std::string type_name){
	//std::cout<<"create:"<<type_name<<std::endl;
	if (!creator.get(type_name)) {
		std::cerr << "UIOBject name:" << type_name
				<< " not exist in this UIObjectCreator" << std::endl;
		return 0;
	}
	return creator.get(type_name)->create_UIObject();
}
void UIObjectCreator::push(UIObject* obj){
	creator.push(obj->get_type(),obj);
}
void UIObjectCreator::initial_creator(){
	push(new UI());
	push(new BuildingUI());

	push(new PictureButton());
	push(new ToggleButton());

	push(new Panel());

	push(new SortGroup());

	push(new PageControl());
	push(new AutoPageControl());

	push(new UIString());

}
} /* namespace UI */
