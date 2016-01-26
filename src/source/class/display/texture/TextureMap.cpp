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
	if (script_path != std::string("NULL")) {
		Load_script(script_path);
	}
}
TextureMap::~TextureMap() {
	//std::cout<<"delete texture map:"<<get_name()<<std::endl;
	std::map<std::string, Texture*>::iterator it = textures.begin();
	while (it != textures.end()) {
		delete (it->second);
		it++;
	}
}
std::string TextureMap::get_name() const {
	return name;
}
void TextureMap::set_name(std::string _name) {
	name = _name;
}

void TextureMap::Parse_Header(std::istream &is, std::string &line) {
	if (line == "FolderPath:") {
		Tim::String::get_line(is, line, true, true);
		folder_path = std::string(line);
	} else if (line == "TextureMapName:") {
		Tim::String::get_line(is, line, true, true);
		set_name(std::string(line));
	}
}
void TextureMap::Parse_texture(std::istream &is) {
	std::string line;
	std::string name, path;
	Tim::String::get_line(is, line, true, true);
	if (line == "TextureName:") {
		Tim::String::get_line(is, name, true, true);
		name = Tim::String::cut(name, std::string("\""));
	} else {
		std::cerr << "Load_texture no Texture Name!!" << line << std::endl;
		return;
	}
	Tim::String::get_line(is, line, true, true);
	if (line == "TexturePath:") {
		Tim::String::get_line(is, line, true, true);
		path = folder_path + line;
	} else {
		std::cerr << "Load_texture no TexturePath!!" << line << std::endl;
		return;
	}
	push_tex(name, Texture2D::loadImage(path.c_str()));
}
void TextureMap::Parse_texture2DArr(std::istream &is) {
	std::string line;
	std::string name, path;
	std::vector<std::string> paths;
	unsigned texnum;
	Tim::String::get_line(is, line, true, true);
	glm::ivec2 size;
	if (line == "TextureName:") {
		Tim::String::get_line(is, name, true, true);
	} else {
		std::cerr << "Load_texture2DArr no Texture Name!!" << line << std::endl;
		return;
	}
	Tim::String::get_line(is, line, true, true);
	if (line == "TextureNum:") {
		Tim::String::get_line(is, line, true, true);
		sscanf(line.c_str(), "%d", &texnum);
	} else {
		std::cerr << "Load_texture2DArr no TextureNum!!" << line << std::endl;
	}
	Tim::String::get_line(is, line, true, true);
	if (line == "TextureSize:") {
		is >> size.x;
		is >> size.y;
	} else {
		std::cerr << "Load_texture2DArr no TextureSize:!!" << line << std::endl;
	}

	for (unsigned i = 0; i < texnum; i++) {
		Tim::String::get_line(is, line, true, true);
		if (line == "TexturePath:") {
			Tim::String::get_line(is, line, true, true);
			path = folder_path + line;
			paths.push_back(path);
		} else {
			std::cerr << "Load_texture2DArr no TexturePath!!" << line
					<< std::endl;
			return;
		}
	}
	Texture2DArr *texarr = Texture2DArr::gen_texture2DArr(paths,
			glm::ivec3(size.x, size.y, paths.size()),
			GL_RGB, GL_RGB, GL_UNSIGNED_BYTE, P_MipMap);
	push_tex(name, texarr);
}
void TextureMap::Parse_textureCubeMap(std::istream &is) {
	std::string line;
	std::string name, path;
	std::vector<std::string> paths;
	Tim::String::get_line(is, line, true, true);
	glm::ivec2 size;
	if (line == "TextureName:") {
		Tim::String::get_line(is, name, true, true);
	} else {
		std::cerr << "Load_textureCubeMap no Texture Name!!" << line
				<< std::endl;
		return;
	}
	Tim::String::get_line(is, line, true, true);
	if (line == "TextureSize:") {
		is >> size.x;
		is >> size.y;
	} else {
		std::cerr << "Load_textureCubeMap no TextureSize:!!" << line
				<< std::endl;
	}

	for (unsigned i = 0; i < 6; i++) {
		Tim::String::get_line(is, line, true, true);
		if (line == "TexturePath:") {
			Tim::String::get_line(is, line, true, true);
			path = folder_path + line;
			paths.push_back(path);
		} else {
			std::cerr << "Load_textureCubeMap no TexturePath!!" << line << ";"
					<< std::endl;
			return;
		}
	}
	TextureCubeMap *texcube = TextureCubeMap::gen_CubeMap(paths,
			glm::ivec2(size.x, size.y),
			GL_RGB, GL_RGB, GL_UNSIGNED_BYTE, P_MipMap);
	push_tex(name, texcube);
}
void TextureMap::Parse_Script(std::istream &is, std::string &line) {
	if (!strcmp(line.c_str(), "Texture:")) {
		Parse_texture(is);
	} else if (!strcmp(line.c_str(), "Texture2DArr:")) {
		Parse_texture2DArr(is);
	} else if (!strcmp(line.c_str(), "TextureCubeMap:")) {
		Parse_textureCubeMap(is);
	}
}
void TextureMap::push_tex(std::string tex_name, Texture* tex) {
	if (textures.find(tex_name) != textures.end()) {
		std::cerr << "texture name:" << tex_name
				<< " already exist in this texture map" << std::endl;
		return;
	}
	textures[tex_name] = tex;
}
Texture* TextureMap::get_tex(std::string tex_name) {
	if (textures.find(tex_name) == textures.end()) {
		std::cerr << "no texture name:" << tex_name << " in this texture map"
				<< std::endl;
		return 0;
	}
	return textures[tex_name];
}
