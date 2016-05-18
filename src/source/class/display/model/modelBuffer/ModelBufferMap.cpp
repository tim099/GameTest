#include "class/display/model/modelBuffer/ModelBufferMap.h"
#include "class/tim/string/String.h"
namespace Display{
ModelBufferMap::ModelBufferMap() {

}
ModelBufferMap::ModelBufferMap(std::string script_path){
	Load_script(script_path);
}
ModelBufferMap::~ModelBufferMap() {

}
std::string ModelBufferMap::get_name() const {
	return name;
}
void ModelBufferMap::set_name(std::string _name) {
	name = _name;
}
void ModelBufferMap::push(std::string name,ModelBuffer* buffer){
	mbuffer_map.push(name,buffer);
}
ModelBuffer* ModelBufferMap::get(std::string name){
	return mbuffer_map.get(name);
}
void ModelBufferMap::Parse_Header(std::istream &is, std::string &line) {
	if (line == "FolderPath:") {
		Tim::String::get_line(is, folder_path, true, true);
	} else if (line == "Name:") {
		Tim::String::get_line(is, line, true, true);
		set_name(std::string(line));
	}
}
void ModelBufferMap::Parse_Script(std::istream &is,std::string &line){
	if(line=="ModelBuffer:"){
		Parse_ModelBuffer(is);
	}
}
void ModelBufferMap::Parse_ModelBuffer(std::istream &is){
	std::string line;
	std::string name, path;
	float size=1.0f;
	bool Align_center=true;
	while(Tim::String::get_line(is, line, true, true)){
		if(line=="#load_end"){
			push(name,new ModelBuffer(folder_path+path,size,Align_center));
			//create
			break;
		}else if(line=="Name:"){
			Tim::String::get_line(is, name, true, true);
		}else if(line=="Path:"){
			Tim::String::get_line(is, path, true, true);
		}else if(line=="Size:"){
			is>>size;
		}else if(line=="Align_center:"){
			Tim::String::get_line(is, line, true, true);
			if(line=="false"){
				Align_center=false;
			}
			else if(line=="true"){
				Align_center=true;
			}
		}

	}
}
}

