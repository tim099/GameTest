#include "class/tim/geometry/2D/RectP2D.h"

namespace Tim {

RectP2D::RectP2D(glm::vec2 _a,glm::vec2 _b) {
	a=Math::min(_a,_b);
	b=Math::max(_a,_b);
}
RectP2D::~RectP2D() {

}
bool RectP2D::coincide(glm::vec2 dot){
	if(Geometry1D::between(glm::vec2(a.x,b.x),dot.x)){
		if(Geometry1D::between(glm::vec2(a.y,b.y),dot.y)){
			return true;
		}
	}
	return false;
}
bool RectP2D::coincide(glm::vec2 dot,glm::vec2 _a,glm::vec2 _b){
	glm::vec2 a=Math::min(_a,_b);
	glm::vec2 b=Math::max(_a,_b);
	if(Geometry1D::between(glm::vec2(a.x,b.x),dot.x)){
		if(Geometry1D::between(glm::vec2(a.y,b.y),dot.y)){
			return true;
		}
	}
	return false;
}
bool RectP2D::coincide(RectP2D *rec){
	if(Geometry1D::coincide(glm::vec2(a.x,b.x),glm::vec2(rec->a.x,rec->b.x))){
		if(Geometry1D::coincide(glm::vec2(a.y,b.y),glm::vec2(rec->a.y,rec->b.y))){
			return true;
		}
	}
	return false;
}
glm::vec2 RectP2D::get_size()const{
	return (b-a);
}
} /* namespace Tim */
