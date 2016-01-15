#include "class/display/texture/texture2D/DrawData2D.h"

DrawData2D::DrawData2D(double _targetaspect,float _alpha,glm::vec2 _pos,float _width) {
	targetaspect=_targetaspect;
	alpha=_alpha;
	pos=_pos;
	width=_width;
}
DrawData2D::~DrawData2D() {

}

