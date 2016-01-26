#ifndef SOURCE_CLASS_DISPLAY_UI_UIOBJECT_H_
#define SOURCE_CLASS_DISPLAY_UI_UIOBJECT_H_
#include <glm/vec2.hpp>
#include <vector>
#include <string>
#include <iostream>
#include "class/input/mouse/selectable/rectangle/SelectableRec.h"
class Draw;
namespace UI {

class UIObject :public SelectableRec{
public:
	UIObject();
	virtual ~UIObject();
	void initial(glm::vec2 pos, glm::vec2 size);
	//=========pure virtual function============
	/*
	 *return a new create object of inherit type
	 */
	virtual UIObject* create_UIObject()=0;
	/*
	 * return the type name of inherit type
	 */
	virtual std::string get_type_name()const=0;

	void Parse_UIObj_Script(std::istream &is,std::string &line);
	void Parse_UIObj_Script(std::ostream &os);


	//===================================

	std::string get_name()const;
	void set_name(std::string name);



	void update_UIObject();
	void draw_UIObject(Draw* draw);

	glm::vec2 get_pos()const;
	/*
	 * return the middle position of UIObject
	 */
	glm::vec2 get_middle_pos() const;

	UIObject* get_parent()const;
	UIObject* get_root();
	/*
	 * find a child(include object itself)which name match and return it's pointer
	 */
	UIObject* get_child(std::string name);
	void set_pos(glm::vec2 pos);
	/*
	 * set cur parent to UIObject* parent
	 */
	void set_parent(UIObject* parent);
	/*
	 * simply set parent to 0
	 */
	void clear_parent();
	/*
	 * push a child UIObject into this
	 */
	void push_child(UIObject* child);
	/*
	 * simply remove child from this object but not delete it
	 */
	void remove_child(UIObject* child);
	/*
	 * delete all child in this UIObject
	 */
	void clear_child();
	void Enable_Mode(int flag);
	void Disable_Mode(int flag);
	bool hide;
protected:
	virtual void Parse_Script(std::istream &is,std::string &line);
	virtual void Parse_Script(std::ostream &os);
	virtual void update();
	virtual void start_draw(Draw* draw);
	//==========SelectableRec implement========
	virtual glm::vec2 get_rec_pos()const;
	virtual glm::vec2 get_rec_size()const;
	//=======================================
	UIObject* parent;
	std::vector<UIObject*>childs;
	std::string name;
	glm::vec2 size;
private:
	glm::vec2 pos;
	int mode;
};

} /* namespace UI */

#endif /* SOURCE_CLASS_DISPLAY_UI_UIOBJECT_H_ */
