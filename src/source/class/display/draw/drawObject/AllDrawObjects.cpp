#include "class/display/draw/drawObject/AllDrawObjects.h"
namespace Display{
AllDrawObjects::AllDrawObjects() {

}
AllDrawObjects::AllDrawObjects(std::string script_path) {
	Load_script(script_path);
}
AllDrawObjects::~AllDrawObjects() {

}
void AllDrawObjects::Parse_map(std::istream &is){
	std::string line;
	std::string scriptPath;
	Tim::String::get_line(is, line, true, true);
	if (line == "ScriptPath:") {
		Tim::String::get_line(is, line, true, true);
		scriptPath = std::string(line);
		DrawObjectMap* map=new DrawObjectMap(folder_path+scriptPath);
		push_map(map);
	}
}
void AllDrawObjects::Parse_dir(std::istream &is){
	std::string line;
	std::string scriptPath;
	Tim::String::get_line(is, line, true, true);
	if (line == "ScriptPath:") {
		Tim::String::get_line(is, line, true, true);
		scriptPath = std::string(line);
		AllDrawObjects* dir=new AllDrawObjects(folder_path+scriptPath);
		push_dir(dir);
	}
}
void AllDrawObjects::Parse_Script(std::istream &is, std::string &line){
	if (line=="Map:") {
		Parse_map(is);
	}else if(line=="Dir:"){
		Parse_dir(is);
	}
}
void AllDrawObjects::Parse_Header(std::istream &is, std::string &line){
	if (line == "Name:") {
		Tim::String::get_line(is, line, true, true);
		set_name(std::string(line));
	}else if (line == "FolderPath:") {
		Tim::String::get_line(is, line, true, true);
		folder_path = std::string(line);
	}
}
}
