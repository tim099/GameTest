#include "class/display/draw/texture/DrawTexture2D.h"
#include "class/display/shader/Shader.h"
DrawTexture2D::DrawTexture2D(Texture *_tex,DrawData2D *_data) {
	tex=_tex;
	data=_data;
}
DrawTexture2D::~DrawTexture2D() {

}
void DrawTexture2D::draw_texture(Shader *shader){
	tex->draw_texture(shader,data);
}
