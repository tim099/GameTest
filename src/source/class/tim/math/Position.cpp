#include "class/tim/math/Position.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
Position::Position(const Position &p) {
	initialize(p.pos,p.r,p.parent_pos);
}
Position::Position(glm::vec3 _pos,glm::vec3 _r,Position *_parent_pos) {
	initialize(_pos,_r,_parent_pos);
}
Position::~Position() {

}
void Position::initialize(glm::vec3 _pos,glm::vec3 _r,Position *_parent_pos){
	pos=_pos;
	r=_r;
	parent_pos=_parent_pos;
}
glm::mat4 Position::PosMat()const{
	glm::mat4 M=glm::mat4(1.0f);
	if(parent_pos)M*=parent_pos->PosMat();
	M*=glm::translate(pos);
	if(r.y!=0.0){
	    glm::mat4 rmat=glm::rotate(r.y,glm::vec3(0,1,0));
	    M*=rmat;
	}
	return M;
}
