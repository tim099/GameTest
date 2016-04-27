#include "class/display/draw/texture/DrawTexture.h"
#include "class/display/font/DrawDataStr.h"
#include "class/display/shader/shader2D/Shader2D.h"
#include <iostream>
namespace Display{
DrawTexture::DrawTexture(Display::Texture *_tex,DrawData* _data) {
	data=_data;
	tex=_tex;
}
DrawTexture::~DrawTexture() {

}
void DrawTexture::draw(Shader2D *shader){
	tex->draw_texture(shader,data);

}
}
