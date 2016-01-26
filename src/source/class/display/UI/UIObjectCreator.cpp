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
	std::map<std::string, UIObject*>::iterator it = creator.begin();
	while (it != creator.end()) {
		delete (it->second);
		it++;
	}
}
UIObject* UIObjectCreator::create(std::string type_name){
	if (creator.find(type_name) == creator.end()) {
		std::cerr << "UIOBject name:" << type_name
				<< " not exist in this UIObjectCreator" << std::endl;
		return 0;
	}
	return creator[type_name]->create_UIObject();
}
void UIObjectCreator::push(UIObject* obj){
	if (creator.find(obj->get_type_name()) != creator.end()) {
		std::cerr << "UIOBject name:" << obj->get_type_name()
				<< " already exist in this UIObjectCreator" << std::endl;
		return;
	}
	obj->set_name(std::string("creatorObj:")+obj->get_type_name());
	std::cout<<"push object"<<obj->get_type_name()<<std::endl;
	creator[obj->get_type_name()]=obj;
}
void UIObjectCreator::initial_creator(){
	//push(new UI()); should't create UI!!
	push(new PictureButton());
	push(new Panel());
}
} /* namespace UI */
