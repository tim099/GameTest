#include "class/display/texture/AllTextures.h"
#include "class/tim/file/File.h"
#include "class/tim/string/String.h"
#include <iostream>
#include <fstream>
namespace Display{
AllTextures::AllTextures(std::string script_path) {
	Load_script(script_path);
}
AllTextures::~AllTextures() {

}
Texture* AllTextures::get_cur_tex(std::string tex_path) {
	return get_cur_object()->get(tex_path);
}
void AllTextures::Parse_Script(std::istream &is, std::string &line) {
	if (line=="TextureMap:") {
		Parse_textureMap(is);
	}else if(line=="TextureDir:"){
		Parse_textureDir(is);
	}
}
void AllTextures::Parse_textureDir(std::istream &is){
	std::string line;
	std::string scriptPath;
	Tim::String::get_line(is, line, true, true);
	if (line == "ScriptPath:") {
		Tim::String::get_line(is, line, true, true);
		scriptPath = std::string(line);
		AllTextures* dir=new AllTextures(folder_path+scriptPath);
		push_dir(dir);
	}
}
void AllTextures::Parse_textureMap(std::istream &is) {
	std::string line;
	std::string scriptPath;
	Tim::String::get_line(is, line, true, true);
	if (line == "ScriptPath:") {
		Tim::String::get_line(is, line, true, true);
		scriptPath = std::string(line);
		TextureMap* map=new TextureMap(folder_path+scriptPath);
		push_map(map);
	}
}
void AllTextures::Parse_Header(std::istream &is, std::string &line) {
	if (line == "Name:") {
		Tim::String::get_line(is, line, true, true);
		set_name(std::string(line));
	}else if (line == "FolderPath:") {
		Tim::String::get_line(is, line, true, true);
		folder_path = std::string(line);
	}
}
}
