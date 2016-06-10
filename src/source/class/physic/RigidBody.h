#ifndef SOURCE_CLASS_PHYSIC_RIGIDBODY_H_
#define SOURCE_CLASS_PHYSIC_RIGIDBODY_H_
#include "class/tim/math/vec3.h"
#include "class/game/entity/Component.h"
#include <cstdio>
#include <string>
namespace physic {

class RigidBody : public entity::Component{
public:
	RigidBody();
	virtual ~RigidBody();
	virtual std::string get_type()const{
		return "RigidBody";
	}
	void save_rigid_body(FILE * file);
	void load_rigid_body(FILE * file);
	void update_rigid_body();

	void set_detect_collision();//call this function every frame to detect collision
	void set_detect_special_collision();//call this function every frame to detect collision
	virtual bool check_collision(RigidBody* b);
	virtual void collide(RigidBody* b);
	virtual void be_collide(RigidBody* b);


	double radius;
	double mass;

	math::vec3<double> vel;
	math::vec3<double> pos,prev_pos;
	RigidBody* collided,*be_collided;
	unsigned collided_id,be_collided_id;
protected:
	virtual void collide_action(RigidBody* b);
	virtual void be_collide_action(RigidBody* b);
};

} /* namespace physic */

#endif /* SOURCE_CLASS_PHYSIC_RIGIDBODY_H_ */
