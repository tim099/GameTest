#ifndef SOURCE_CLASS_PHYSIC_RIGIDBODY_H_
#define SOURCE_CLASS_PHYSIC_RIGIDBODY_H_
#include "class/tim/math/vec3.h"
#include <cstdio>
#include <string>
namespace physic {

class RigidBody {
public:
	RigidBody();
	virtual ~RigidBody();
	virtual std::string get_type()const{
		return "RigidBody";
	}
	void save(FILE * file);
	void load(FILE * file);
	void update_rigid_body();

	void set_detect_collision();//call this function every frame to detect collision
	void set_detect_special_collision();//call this function every frame to detect collision
	virtual bool check_collision(RigidBody* b);
	virtual void collide(RigidBody* b);
	virtual void be_collide(RigidBody* b);
	double radius;
	double mass;
	math::vec3<double> acc;
	math::vec3<double> vel;
	math::vec3<double> pos,prev_pos;
	RigidBody* collided,*be_collided;
};

} /* namespace physic */

#endif /* SOURCE_CLASS_PHYSIC_RIGIDBODY_H_ */
