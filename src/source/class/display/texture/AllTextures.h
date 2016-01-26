#ifndef SOURCE_CLASS_DISPLAY_TEXTURE_ALLTEXTURES_H_
#define SOURCE_CLASS_DISPLAY_TEXTURE_ALLTEXTURES_H_
#include "class/display/texture/TextureMap.h"
#include <map>
class AllTextures : public Tim::Parser {
	static AllTextures* cur_allTextures;
public:
	AllTextures(std::string script_path);
	virtual ~AllTextures();
	std::string get_name()const;
	void set_name(std::string name);
	/*
	 * add texture map into all_textures
	 */
	void push_textureMap(TextureMap* tex_map);
	/*
	 * get texture map by name
	 */
	TextureMap* get_textureMap(std::string name);
	/*
	 * add a dir
	 */
	void push_dir(AllTextures* dir);

	/*
	 * get a dir by name
	 */
	AllTextures* get_dir(std::string name);

	/*
	 * register as cur AllTextures
	 */
	void rigister();
	/*
	 * get texture from cur registered AllTextures
	 */
	static Texture* get_cur_tex(std::string tex_path);
	Texture* get_tex(std::string tex_path);
protected:
	void Parse_textureMap(std::istream &is);
	void Parse_textureDir(std::istream &is);
	virtual inline std::string Script_name()const{
		return "#LOAD_ALL_TEXTURES_SCRIPT";
	}
	virtual void Parse_Script(std::istream &is,std::string &line);
	virtual void Parse_Header(std::istream &is,std::string &line);
	std::map<std::string,TextureMap*>texture_maps;
	std::map<std::string,AllTextures*>texture_dirs;

	std::string name;
};

#endif /* SOURCE_CLASS_DISPLAY_TEXTURE_ALLTEXTURES_H_ */
