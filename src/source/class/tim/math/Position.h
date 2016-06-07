#ifndef POSITION_H_
#define POSITION_H_
//#include <GL/glew.h>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
namespace math {
class Position {
public:
	Position();
	Position(const Position &p);
	Position(glm::vec3 pos,glm::vec3 r=glm::vec3(0,0,0),Position *parent_pos=0);
	virtual ~Position();


	void init(const Position &p);
	void init(glm::vec3 pos,glm::vec3 r,Position *parent_pos=0);

	glm::mat4 get_pos_mat();

	void set_parent(Position *_parent_pos){
		parent_pos=_parent_pos;
	}

	void set_ry(float ry);//r =rotate angle in Euler angle
	void set_r(glm::vec3 r);
	glm::vec3 get_r()const;

	void set_pos(glm::vec3 pos);
	glm::vec3 get_pos()const;

	glm::mat4 get_rotate_mat()const{return r_mat;}

	void set_scale(glm::vec3 scale);
protected:
	/*
	 * need a normalize axis
	 */
	glm::quat get_quaternion(glm::vec3 axis,float angle);
	glm::vec4 multiply_quaternion(glm::vec4 a,glm::vec4 b);
	Position *parent_pos;

	glm::vec3 pos;
	glm::vec3 r;
	glm::vec3 scale;

	//for performance improvement(but take more space
	bool updated;
	bool rotated_x,rotated_y,rotated_z;

	glm::quat quat_x,quat_y,quat_z;

	glm::mat4 r_mat;
	glm::mat4 pos_matrix;

};
}
#endif /* POSITION_H_ */
