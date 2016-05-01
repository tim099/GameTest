#include "class/display/model/modelBuffer/AllModelBuffers.h"
namespace Display{
AllModelBuffers::AllModelBuffers() {

}
AllModelBuffers::AllModelBuffers(std::string script_path) {
	Load_script(script_path);
}
AllModelBuffers::~AllModelBuffers() {

}
ModelBuffer *AllModelBuffers::get_cur_model(std::string obj_path){
	return AllModelBuffers::get_cur_object()->get(obj_path);
}
void AllModelBuffers::Parse_map(std::istream &is){
	std::string line;
	std::string scriptPath;
	Tim::String::get_line(is, line, true, true);
	if (line == "ScriptPath:") {
		Tim::String::get_line(is, line, true, true);
		scriptPath = std::string(line);
		ModelBufferMap* map=new ModelBufferMap(folder_path+scriptPath);
		push_map(map);
	}
}
void AllModelBuffers::Parse_dir(std::istream &is){
	std::string line;
	std::string scriptPath;
	Tim::String::get_line(is, line, true, true);
	if (line == "ScriptPath:") {
		Tim::String::get_line(is, line, true, true);
		scriptPath = std::string(line);
		AllModelBuffers* dir=new AllModelBuffers(folder_path+scriptPath);
		push_dir(dir);
	}
}
void AllModelBuffers::Parse_Script(std::istream &is, std::string &line){
	if (line=="Map:") {
		Parse_map(is);
	}else if(line=="Dir:"){
		Parse_dir(is);
	}
}
void AllModelBuffers::Parse_Header(std::istream &is, std::string &line){
	if (line == "Name:") {
		Tim::String::get_line(is, line, true, true);
		set_name(std::string(line));
	}else if (line == "FolderPath:") {
		Tim::String::get_line(is, line, true, true);
		folder_path = std::string(line);
	}
}
}
