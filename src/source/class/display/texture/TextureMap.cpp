#include "class/display/texture/TextureMap.h"
#include "class/display/texture/texture2D/Texture2D.h"
#include "class/tim/file/File.h"
#include "class/tim/string/String.h"
#include <cstdio>
#include <string>
#include <cstring>
#include <iostream>
#include <fstream>
TextureMap::TextureMap(std::string script_path) {
	if(script_path!=std::string("NULL")){
		Load_texture_script(script_path);
	}
}
TextureMap::~TextureMap() {
	std::map<std::string,Texture*>::iterator it=textures.begin();
	while(it!=textures.end()){
		delete (it->second);
		it++;
	}
}
void TextureMap::Load_texture(std::istream &is,const std::string &folder_path){
	std::string line;
	std::string name,path;
	Tim::String::get_line(is,line,true,true);
	if(line=="TextureName:"){
		Tim::String::get_line(is,name,true,true);
	}else{
		std::cerr<<"Load_texture no Texture Name!!"<<line<<std::endl;
		return;
	}
	Tim::String::get_line(is,line,true,true);
	if(line=="TexturePath:"){
		Tim::String::get_line(is,line,true,true);
		path=folder_path+line;
	}else{
		std::cerr<<"Load_texture no TexturePath!!"<<line<<std::endl;
		return;
	}
	push_tex(name,Texture2D::loadBMP(path.c_str()));
}
void TextureMap::Load_Header(std::istream &is,std::string &folder_path){
	std::string line;
	if(Tim::String::get_line(is,line,true,true)&&line!="FolderPath:"){
		std::cerr<<"Load_Header No FolderPath!!"<<line<<std::endl;
		return;
	}
	Tim::String::get_line(is,line,true,true);
	folder_path=std::string(line);
	if(Tim::String::get_line(is,line,true,true)&&line!="#HEADER_END"){
		std::cerr<<"Load_Header No #HEADER_END!!"<<line<<std::endl;
		return;
	}
}
void TextureMap::Load_texture_script(std::string script_path){
	std::string line;
	std::filebuf file;

	file.open(script_path.c_str(),std::ios::in);
	std::istream is(&file);
	if(Tim::String::get_line(is,line,true,true)&&line!="#LOADTEXTURE_SCRIPT"){
		std::cerr<<"Load_texture Fail:"<<script_path<<std::endl;
		return;
	}
	std::string folder_path;
	if(Tim::String::get_line(is,line,true,true)&&line!="#HEADER"){
		std::cerr<<"Load_texture No Header!!"<<line<<std::endl;
		return;
	}else{
		Load_Header(is,folder_path);
	}
	while(!is.eof()){
		Tim::String::get_line(is,line,true,true);
		if(line=="#END"){
			break;
		}
		if(!strcmp(line.c_str(),"Texture:")){
			Load_texture(is,folder_path);
		}
	}

	file.close();
}
void TextureMap::push_tex(std::string tex_name,Texture* tex){
	textures[tex_name]=tex;
}
Texture* TextureMap::get_tex(std::string tex_name){
	return textures[tex_name];
}
