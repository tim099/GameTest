#include "class/display/texture/texture2D/DrawData2D.h"
namespace Display{
DrawData2D::DrawData2D(float _alpha,glm::vec2 _pos,float _width, float _height) {
	alpha=_alpha;
	pos=_pos;
	width=_width;
	height=_height;
}
DrawData2D::~DrawData2D() {

}
}
