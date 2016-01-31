#include "class/display/draw/drawObject/DrawObjectMap.h"
#include "class/tim/string/String.h"
#include "class/display/draw/Draw.h"
DrawObjectMap::DrawObjectMap() {

}
DrawObjectMap::DrawObjectMap(std::string script_path) {
	Load_script(script_path);
}
DrawObjectMap::~DrawObjectMap() {

}
std::string DrawObjectMap::get_name()const{
	return name;
}
void DrawObjectMap::set_name(std::string _name){
	name=_name;
}
void DrawObjectMap::push(std::string name,DrawObject* obj){
	objs.push(name,obj);
}
DrawObject* DrawObjectMap::get(std::string name){
	return objs.get(name);
}
void DrawObjectMap::Parse_Header(std::istream &is, std::string &line) {
	if (line == "FolderPath:") {
		Tim::String::get_line(is, line, true, true);
		folder_path = std::string(line);
	} else if (line == "Name:") {
		Tim::String::get_line(is, line, true, true);
		set_name(std::string(line));
	}
}
void DrawObjectMap::Parse_Script(std::istream &is,std::string &line){
	if(line=="DrawObject:"){
		Parse_DrawObject(is);
	}
}
void DrawObjectMap::Parse_DrawObject(std::istream &is){
	std::string line;
	std::string name;
	std::string texture,normalmap;
	std::string modelbuffer;
	bool have_mat=false;
	bool draw_shadow=true;
	glm::vec4 mat;
	while(Tim::String::get_line(is, line, true, true)){
		if(line=="#load_end"){
			DrawObject* d_obj=new DrawObject(modelbuffer,texture,normalmap);
			if(have_mat)d_obj->mat=mat;
			d_obj->draw_shadow=draw_shadow;
			push(name,d_obj);
			//create
			break;
		}else if(line=="Name:"){
			Tim::String::get_line(is, name, true, true);
		}else if(line=="ModelBuffer:"){
			Tim::String::get_line(is, modelbuffer, true, true);
		}else if(line=="Texture:"){
			Tim::String::get_line(is, texture, true, true);
		}else if(line=="NormalMap:"){
			Tim::String::get_line(is, normalmap, true, true);
		}else if(line=="Material:"){
			have_mat=true;
			is>>mat.x;
			is>>mat.y;
			is>>mat.z;
			is>>mat.w;
		}else if(line=="DrawShadow:"){
			Tim::String::get_line(is, line, true, true);
			if(line=="false"){
				draw_shadow=false;
			}
		}
	}
}