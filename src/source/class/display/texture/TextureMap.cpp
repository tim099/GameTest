#include "class/display/texture/TextureMap.h"
#include "class/display/texture/texture2D/Texture2D.h"
#include "class/display/texture/texture3D/Texture2DArr/Texture2DArr.h"
#include "class/display/texture/texture3D/cubemap/TextureCubeMap.h"
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
void TextureMap::Load_texture2DArr(std::istream &is,const std::string &folder_path){
	std::string line;
	std::string name,path;
	std::vector<std::string>paths;
	unsigned texnum;
	Tim::String::get_line(is,line,true,true);
	glm::ivec2 size;
	if(line=="TextureName:"){
		Tim::String::get_line(is,name,true,true);
	}else{
		std::cerr<<"Load_texture2DArr no Texture Name!!"<<line<<std::endl;
		return;
	}
	Tim::String::get_line(is,line,true,true);
	if(line=="TextureNum:"){
		Tim::String::get_line(is,line,true,true);
		sscanf(line.c_str(),"%d",&texnum);
	}else{
		std::cerr<<"Load_texture2DArr no TextureNum!!"<<line<<std::endl;
	}
	Tim::String::get_line(is,line,true,true);
	if(line=="TextureSize:"){
		is>>size.x;
		is>>size.y;
	}else{
		std::cerr<<"Load_texture2DArr no TextureSize:!!"<<line<<std::endl;
	}

	for(unsigned i=0;i<texnum;i++){
		Tim::String::get_line(is,line,true,true);
		if(line=="TexturePath:"){
			Tim::String::get_line(is,line,true,true);
			path=folder_path+line;
			paths.push_back(path);
		}else{
			std::cerr<<"Load_texture2DArr no TexturePath!!"<<line<<std::endl;
			return;
		}
	}
	Texture2DArr *texarr=Texture2DArr::gen_texture2DArr(paths,glm::ivec3(size.x,size.y,paths.size()),
			GL_RGB,GL_RGB,GL_UNSIGNED_BYTE,P_MipMap);
	push_tex(name,texarr);
}
void TextureMap::Load_textureCubeMap(std::istream &is,const std::string &folder_path){
	std::string line;
	std::string name,path;
	std::vector<std::string>paths;
	Tim::String::get_line(is,line,true,true);
	glm::ivec2 size;
	if(line=="TextureName:"){
		Tim::String::get_line(is,name,true,true);
	}else{
		std::cerr<<"Load_textureCubeMap no Texture Name!!"<<line<<std::endl;
		return;
	}
	Tim::String::get_line(is,line,true,true);
	if(line=="TextureSize:"){
		is>>size.x;
		is>>size.y;
	}else{
		std::cerr<<"Load_textureCubeMap no TextureSize:!!"<<line<<std::endl;
	}

	for(unsigned i=0;i<6;i++){
		Tim::String::get_line(is,line,true,true);
		if(line=="TexturePath:"){
			Tim::String::get_line(is,line,true,true);
			path=folder_path+line;
			paths.push_back(path);
		}else{
			std::cerr<<"Load_textureCubeMap no TexturePath!!"<<line<<";"<<std::endl;
			return;
		}
	}
	TextureCubeMap *texcube=TextureCubeMap::gen_CubeMap(paths,glm::ivec2(size.x,size.y),
			GL_RGB,GL_RGB,GL_UNSIGNED_BYTE,P_MipMap);
	push_tex(name,texcube);
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
		}else if(!strcmp(line.c_str(),"Texture:")){
			Load_texture(is,folder_path);
		}else if(!strcmp(line.c_str(),"Texture2DArr:")){
			Load_texture2DArr(is,folder_path);
		}else if(!strcmp(line.c_str(),"TextureCubeMap:")){
			Load_textureCubeMap(is,folder_path);
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
