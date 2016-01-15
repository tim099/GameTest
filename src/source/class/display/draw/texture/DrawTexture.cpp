#include "class/display/draw/texture/DrawTexture.h"
#include "class/display/shader/shader2D/Shader2D.h"
#include <iostream>
DrawTexture::DrawTexture(Texture *_tex,DrawData* _data) {
	data=_data;
	tex=_tex;
}
DrawTexture::~DrawTexture() {

}
void DrawTexture::draw(Shader *shader){
	tex->draw_texture(shader,data);
}

