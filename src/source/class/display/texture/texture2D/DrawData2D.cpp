#include "class/display/texture/texture2D/DrawData2D.h"

DrawData2D::DrawData2D(double _targetaspect,float _alpha,glm::vec2 _pos,float _size) {
	targetaspect=_targetaspect;
	alpha=_alpha;
	pos=_pos;
	size=_size;
}
DrawData2D::~DrawData2D() {

}

