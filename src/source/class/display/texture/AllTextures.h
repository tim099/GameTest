#ifndef SOURCE_CLASS_DISPLAY_TEXTURE_ALLTEXTURES_H_
#define SOURCE_CLASS_DISPLAY_TEXTURE_ALLTEXTURES_H_
#include "class/display/texture/TextureMap.h"
#include "class/tim/map/MapContainer.h"
#include "class/tim/map/MapTree.h"
#include "class/tim/globalObject/GlobalObject.h"
#include <map>
namespace Display{
class AllTextures: public Tim::Parser,
		public Tim::MapTree<TextureMap, Texture>,
		public Tim::GlobalObject<AllTextures> {

public:
	AllTextures(std::string script_path);
	virtual ~AllTextures();

	/*
	 * get texture from cur registered AllTextures
	 */
	static Texture* get_cur_tex(std::string tex_path);

protected:
	void Parse_textureMap(std::istream &is);
	void Parse_textureDir(std::istream &is);
	virtual inline std::string Script_name() const {
		return "#LOAD_ALL_TEXTURES_SCRIPT";
	}
	virtual void Parse_Script(std::istream &is, std::string &line);
	virtual void Parse_Header(std::istream &is, std::string &line);
	std::string folder_path;
};
}
#endif /* SOURCE_CLASS_DISPLAY_TEXTURE_ALLTEXTURES_H_ */
