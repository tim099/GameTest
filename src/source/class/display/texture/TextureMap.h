#ifndef TEXTUREMAP_H_
#define TEXTUREMAP_H_

#include "class/display/texture/Texture.h"
#include "class/tim/parser/Parser.h"
#include <string>
#include <map>
class TextureMap : public Tim::Parser{
public:
	TextureMap(std::string script_path=std::string("NULL"));
	virtual ~TextureMap();
	std::string get_name()const;
	void set_name(std::string name);

	void push_tex(std::string tex_name,Texture* tex);
	Texture* get_tex(std::string tex_name);
protected:
	void Parse_texture(std::istream &is);
	void Parse_texture2DArr(std::istream &is);
	void Parse_textureCubeMap(std::istream &is);


	virtual inline std::string Script_name()const{
		return "#LOAD_TEXTUREMAP_SCRIPT";
	}
	virtual void Parse_Script(std::istream &is,std::string &line);
	virtual void Parse_Header(std::istream &is,std::string &line);

	std::map<std::string,Texture*>textures;
	std::string folder_path;
	std::string name;
};

#endif /* TEXTUREMAP_H_ */
