#include "class/display/UI/UIObjectCreator.h"
#include "class/display/UI/UI.h"
#include "class/display/UI/button/pictureButton/PictureButton.h"
#include "class/display/UI/panel/Panel.h"
#include <iostream>
namespace UI {

UIObjectCreator::UIObjectCreator() {
	initial_creator();
}
UIObjectCreator::~UIObjectCreator() {

}
UIObject* UIObjectCreator::create(std::string type_name){
	if (!creator.get(type_name)) {
		std::cerr << "UIOBject name:" << type_name
				<< " not exist in this UIObjectCreator" << std::endl;
		return 0;
	}
	return creator.get(type_name)->create_UIObject();
}
void UIObjectCreator::push(UIObject* obj){
	creator.push(obj->get_type_name(),obj);
}
void UIObjectCreator::initial_creator(){
	push(new PictureButton());
	push(new Panel());
}
} /* namespace UI */
