#ifndef SOURCE_CLASS_DISPLAY_UI_PAGE_AUTOPAGECONTROL_H_
#define SOURCE_CLASS_DISPLAY_UI_PAGE_AUTOPAGECONTROL_H_

#include "class/display/UI/page/PageControl.h"

namespace UI {
class PictureButton;
class AutoPageControl: public PageControl {
public:
	AutoPageControl();
	virtual ~AutoPageControl();
	virtual UIObject* create_UIObject(){
		return new AutoPageControl();
	}
	virtual std::string get_type()const{
		return "AutoPageControl";
	}

	void create_pages(std::vector<std::string> &names);
	void update_pages();
	void set_path(std::string load_path);
protected:
	virtual bool save_child()const{
		return false;
	}
	virtual void Parse_UIScript(std::istream &is,std::string &line);
	virtual void Parse_UIScript(std::ostream &os);
	void Parse_button_template(std::istream &is,std::string &line);
	void Parse_button_template(std::ostream &os);
	int button_per_page;
	PictureButton* button_template;
	std::string sent_to;
	std::string load_path;
	glm::vec2 interval;
	bool create_by_files;
	bool create_by_dirs;
};

} /* namespace UI */

#endif /* SOURCE_CLASS_DISPLAY_UI_PAGE_AUTOPAGECONTROL_H_ */
