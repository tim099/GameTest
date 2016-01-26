#include "class/display/texture/AllTextures.h"
#include "class/tim/file/File.h"
#include "class/tim/string/String.h"
#include <iostream>
#include <fstream>
AllTextures* AllTextures::cur_allTextures = 0;
AllTextures::AllTextures(std::string script_path) {
	Load_script(script_path);
	rigister();
}
AllTextures::~AllTextures() {
	//std::cout<<"delete AllTextures:"<<get_name()<<std::endl;
	std::map<std::string, TextureMap*>::iterator it = texture_maps.begin();
	while (it != texture_maps.end()) {
		delete (it->second);
		it++;
	}
	std::map<std::string, AllTextures*>::iterator it2 = texture_dirs.begin();
	while (it2 != texture_dirs.end()) {
		delete (it2->second);
		it2++;
	}
}
std::string AllTextures::get_name() const {
	return name;
}
void AllTextures::set_name(std::string _name) {
	name = _name;
}
void AllTextures::rigister() {
	cur_allTextures = this;
}
Texture* AllTextures::get_cur_tex(std::string tex_path) {
	return cur_allTextures->get_tex(tex_path);
}
Texture* AllTextures::get_tex(std::string tex_path) {
	std::vector<std::string> path;
	Tim::String::split(tex_path, "/", path);
	if (path.size() == 2) {
		TextureMap *tex_map = get_textureMap(path.at(0));
		if (tex_map) {
			return tex_map->get_tex(path.at(1));
		}
	} else if (path.size() > 2) { //bigger than 2
		AllTextures* dir=get_dir(path.at(0));
		if(dir){
			std::string new_path;
			for(unsigned i=1;i<path.size();i++){
				new_path+="/"+path.at(i);
			}
			return dir->get_tex(new_path);
		}
	}
	return 0;
}
void AllTextures::push_dir(AllTextures* dir) {
	if (texture_dirs.find(dir->get_name()) != texture_dirs.end()) {
		std::cerr << "AllTextures dir name:" << dir->get_name()
				<< " already exist in AllTextures,please rename it"
				<< std::endl;
		return;
	}
	texture_dirs[dir->get_name()] = dir;
}
AllTextures* AllTextures::get_dir(std::string name){
	if (texture_dirs.find(name) == texture_dirs.end()) {
		std::cerr << "AllTextures dir name:" << name
				<< " not exist in AllTextures"
				<< std::endl;
		return 0;
	}
	return texture_dirs[name];
}
void AllTextures::push_textureMap(TextureMap* tex_map) {
	if (texture_maps.find(tex_map->get_name()) != texture_maps.end()) {
		std::cerr << "texture map name:" << tex_map->get_name()
				<< " already exist in AllTextures,please rename it"
				<< std::endl;
		return;
	}
	texture_maps[tex_map->get_name()] = tex_map;
}
TextureMap* AllTextures::get_textureMap(std::string name) {
	if (texture_maps.find(name) == texture_maps.end()) {
		std::cerr << "texture map name:" << name << " not exist in AllTextures"
				<< std::endl;
		return 0;
	}
	return texture_maps[name];

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
		AllTextures *dir = new AllTextures(scriptPath);
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
		TextureMap *tex_map = new TextureMap(scriptPath);
		push_textureMap(tex_map);
	}
}
void AllTextures::Parse_Header(std::istream &is, std::string &line) {
	if (line == "AllTexturesName:") {
		Tim::String::get_line(is, line, true, true);
		set_name(std::string(line));
	}
}
