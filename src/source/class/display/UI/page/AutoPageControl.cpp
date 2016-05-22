#include "class/display/UI/page/AutoPageControl.h"
#include "class/display/UI/button/pictureButton/PictureButton.h"
#include "class/input/signal/Signal.h"
#include "class/display/UI/group/SortGroup.h"
#include "class/tim/file/File.h"
#include <cmath>
namespace UI {

AutoPageControl::AutoPageControl() {
	button_per_page=1;
	button_template=0;
	create_by_files=false;
	create_by_dirs=false;
}
AutoPageControl::~AutoPageControl() {
	if(button_template)delete button_template;
}
void AutoPageControl::set_path(std::string _load_path){
	load_path=_load_path;
}
void AutoPageControl::Parse_button_template(std::ostream &os){
	button_template->Parse_texture(os);
	os<<"	"<<"#create_template_end"<<std::endl;
}
void AutoPageControl::Parse_button_template(std::istream &is,std::string &line){
	if(button_template)delete button_template;
	button_template=new PictureButton();
	while (Tim::String::get_line(is, line, true, true)) {
		if (line == "#create_template_end") {
			button_template->set_texture();
			break;
		}else{
			button_template->Parse_texture(is,line);
		}
	}
}
void AutoPageControl::create_pages(std::vector<std::string> &names){
	clear_child();
	if(names.empty())return;
	int page_num=(names.size()/button_per_page);
	int cur_name=0;
	PictureButton *cur_but;
	SortGroup* cur_group;
	if(names.size()%button_per_page!=0)page_num++;

	for(int i=0;i<page_num;i++){
		cur_group=new SortGroup();
		cur_group->set_interval(interval);
		push_child(cur_group);
		for(int j=0;j<button_per_page;j++){
			cur_but=(PictureButton *)button_template->copy_UIObject();
			cur_but->set_string(new std::string(names.at(cur_name)),0);
			cur_but->set_signal(new Input::Signal(names.at(cur_name),sent_to));
			cur_group->push_child(cur_but);
			cur_name++;
			if(cur_name>=(int)names.size())break;
		}
	}
	size=glm::vec2(button_template->get_size().x,fabs(interval.y)*button_per_page);
}
void AutoPageControl::update_pages(){
	if(create_by_files){
		std::vector<std::string> files=Tim::File::get_all_files(load_path);
		create_pages(files);
	}else if(create_by_dirs){
		std::vector<std::string> dirs=Tim::File::get_all_dirs(load_path);
		create_pages(dirs);
	}
}
void AutoPageControl::Parse_UIScript(std::istream &is, std::string &line) {
	if(line=="ButtonTemplate:"){
		Parse_button_template(is,line);
	}else if(line=="Sent_to:"){
		Tim::String::get_line(is, sent_to, true, true);
	}else if (line == "Interval:") {
		is>>interval.x;
		is>>interval.y;
	}else if(line=="ButtonPerPage:"){
		is>>button_per_page;
	}else if(line == "LoadPath:"){
		Tim::String::get_line(is, load_path, true, true);
	}else if(line == "#LoadFilesToButtons"){
		if(!button_template){
			std::cerr<<"AutoPageControl::Parse_UIScript LoadFilesToButton: fail"
					<<"no button_template created"<<std::endl;
			return;
		}
		create_by_files=true;
		update_pages();
	}else if(line == "#LoadDirsToButtons"){
		if(!button_template){
			std::cerr<<"AutoPageControl::Parse_UIScript LoadDirsToButtons: fail"
					<<"no button_template created"<<std::endl;
			return;
		}
		create_by_dirs=true;
		update_pages();
	}

}
void AutoPageControl::Parse_UIScript(std::ostream &os) {
	os<<"	"<<"ButtonTemplate:"<<std::endl;
	Parse_button_template(os);
	os<<"	"<<"Sent_to:"<<std::endl;
	os<<"		"<<sent_to<<std::endl;
	os<<"	"<<"Interval:"<<std::endl;
	os<<"		"<<interval.x<<" "<<interval.y<<std::endl;
	os<<"	"<<"ButtonPerPage:"<<std::endl;
	os<<"		"<<button_per_page<<std::endl;
	os<<"	"<<"LoadPath:"<<std::endl;
	os<<"		"<<load_path<<std::endl;
	if(create_by_files){
		os<<"	"<<"#LoadFilesToButtons"<<std::endl;
	}
	if(create_by_dirs){
		os<<"	"<<"#LoadDirsToButtons"<<std::endl;
	}
}
} /* namespace UI */
