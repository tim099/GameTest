#ifndef TEXTUREMAP_H_
#define TEXTUREMAP_H_

#include "class/display/texture/Texture.h"

#include <string>
#include <map>
class TextureMap {
public:
	TextureMap(std::string script_path=std::string("NULL"));
	virtual ~TextureMap();
	void Load_texture_script(std::string script_path);
	void push_tex(std::string tex_name,Texture* tex);
	Texture* get_tex(std::string tex_name);
protected:
	void Load_texture(std::istream &is,const std::string &folder_path);
	void Load_texture2DArr(std::istream &is,const std::string &folder_path);
	void Load_Header(std::istream &is,std::string &folder_path);
	std::map<std::string,Texture*>textures;
};

#endif /* TEXTUREMAP_H_ */
