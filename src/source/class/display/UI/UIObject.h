#ifndef SOURCE_CLASS_DISPLAY_UI_UIOBJECT_H_
#define SOURCE_CLASS_DISPLAY_UI_UIOBJECT_H_
#include <glm/vec2.hpp>
#include <vector>
#include <string>
#include <iostream>
#include "class/input/mouse/selectable/rectangle/SelectableRec.h"
#include "class/tim/string/String.h"
#include "class/tim/math/vec2.h"
namespace Display{
class Draw;
}

namespace Input{
class Receiver;
}

namespace UI {
class UIObjectCreator;

namespace Mode{
	static const int EDIT=1<<0;
}
class UIObject : public Input::SelectableRec{
public:
	UIObject();
	virtual ~UIObject();

	void init(math::vec2<float> _pos, math::vec2<float> _size){
		set_pos(_pos);
		size = _size;
	}
	//=========pure virtual function============

	//return a new create object of inherit type
	virtual UIObject* create_UIObject()=0;
	virtual UIObject* copy_UIObject();
	//return the type name of inherit type
	virtual std::string get_type()const=0;

	virtual void Parse_UIObj_Script(UIObject* cur_root,std::istream &is,std::string &line);
	virtual void Parse_UIObj_Script(std::ostream &os);
	//===================================

	std::string get_name()const;
	void set_name(std::string name);

	//update this UIObject and it's children
	void update_UIObject();

	//draw this UIObject and it's children
	void draw_UIObject(Display::Draw* draw);


	math::vec2<float> get_size()const{
		return size;
	}
	//get position
	math::vec2<float> get_pos()const{
		if (parent) {
			return pos + parent->get_pos();
		}
		return pos;
	}
	//get relative position to parent
	math::vec2<float> get_relative_pos()const{
		return pos;
	}

	//return the middle position of UIObject
	math::vec2<float> get_middle_pos() const{
		return get_pos() + math::vec2<float>(0.5 * size.x, -0.5 * size.y);
	}

	UIObject* get_parent()const;
	UIObject* get_root();

	//find a child(include object itself)which name match and return it's pointer
	UIObject* get_child(std::string name);

	//search UIObject in this Object's root(search the whole UI Tree
	UIObject* search_root(std::string name);

	//set relative position to parent
	void set_relative_pos(math::vec2<float> _pos){
		pos = _pos;
	}

	//set texture space position
	void set_pos(math::vec2<float> _pos){
		pos = _pos;
		if (parent)
			pos -= parent->get_pos();
	}

	//set cur parent to UIObject* parent
	void set_parent(UIObject* parent);

	//simply set parent to 0
	void clear_parent();

	//push a child UIObject into this
	void push_child(UIObject* child);

	//simply remove child from this object but not delete it
	void remove_child(UIObject* child);

	//delete all child in this UIObject
	void clear_child();
	//Enable a mode by flag(UI::Mode::(mode_type))
	void Enable_Mode(int flag);

	//Disable a mode by flag(UI::Mode::(mode_type))
	void Disable_Mode(int flag);

	//return true if mode active
	bool check_mode(int mode)const;

	//set_receiver for this UIObject
	void set_receiver(std::string receiver_name);


	//hide this UIObject and it's childs if hide = ture
	bool hide;
protected:
	/*determine if child under this UIObject should be save by UIObject
	 * or inherit class will handle itself(return false if handle itself)
	 */
	virtual bool save_child()const{
		return true;
	}
	virtual void Parse_UIScript(std::istream &is,std::string &line);
	virtual void Parse_UIScript(std::ostream &os);
	virtual void update();
	virtual void start_draw(Display::Draw* draw);
	//==========SelectableRec implement========
	virtual math::vec2<float> get_rec_pos()const{
		return get_pos();
	}
	virtual math::vec2<float> get_rec_size()const{
		return size;
	}
	//=======================================
	UIObject* parent;
	std::vector<UIObject*>childs;
	std::string name;
	math::vec2<float> size;
	Input::Receiver *receiver;
	UIObjectCreator* creator;
private:
	math::vec2<float> pos;
	int mode;
};

} /* namespace UI */

#endif /* SOURCE_CLASS_DISPLAY_UI_UIOBJECT_H_ */
