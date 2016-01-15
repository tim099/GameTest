#include "class/tim/geometry/1D/Geometry1D.h"

namespace Tim {

Geometry1D::Geometry1D() {

}
Geometry1D::~Geometry1D() {

}
bool Geometry1D::between(glm::vec2 line,float dot){
	if((line.x-dot)*(line.y-dot)<=0.0f)return true;
	else return false;
}
bool Geometry1D::coincide(glm::vec2 line_a,glm::vec2 line_b){
	if(between(line_a,line_b.x))return true;
	if(between(line_a,line_b.y))return true;
	if(between(line_b,line_a.x))return true;//if line_b is longer than line_a and line_a totally inside line_b

	return false;
}
} /* namespace Tim */
