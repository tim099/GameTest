#ifndef SOURCE_CLASS_DISPLAY_FONT_STRINGRENDERER_H_
#define SOURCE_CLASS_DISPLAY_FONT_STRINGRENDERER_H_
#include "class/display/font/RenderString.h"
#include <vector>

class Shader2D;
class Texture2D;
class Buffer;
class StringRenderer {
public:
	static const double Font_seg = 1.0 / 16.0;
	static const int TAB_SIZE = 5;
	StringRenderer(std::string fontTexturePath);
	virtual ~StringRenderer();
	void push(RenderString* renderStr);
	void render(Shader2D* shader2D, RenderString* renderStr);
	void render_text(unsigned char c);
	void draw(Shader2D* shader2D);
	void clear();
protected:
	std::vector<RenderString*> render_strs;
	Texture2D* fontTexture;
	float vertex_buffer_data[18];
	float uv_buffer_data[12];
	float targetaspect;
	Buffer *vtbuffer;
	Buffer *uvbuffer;
};

#endif /* SOURCE_CLASS_DISPLAY_FONT_STRINGRENDERER_H_ */
