#ifndef SOURCE_CLASS_PHYSIC_RIGIDBODYCONTROLLER_H_
#define SOURCE_CLASS_PHYSIC_RIGIDBODYCONTROLLER_H_

#include "class/controller/Controller.h"
#include "class/physic/RigidBody.h"
#include "class/tim/globalObject/GlobalObject.h"
#include <vector>
namespace physic {

class RigidBodyController: public Controller ,public Tim::GlobalObject<RigidBodyController>{
public:
	RigidBodyController();
	virtual ~RigidBodyController();
	void push_collision(RigidBody* rigid_body){
		collisions.push_back(rigid_body);
	}
	void push_special_collision(RigidBody* rigid_body){
		special_collisions.push_back(rigid_body);
	}
	bool check_collision(RigidBody* rigid_body);
	virtual void pre_update();
	virtual void update();
protected:
	void check_collision();
	bool detect_collision(RigidBody* rigid_body);

	//std::vector<RigidBody*>rigid_bodys;
	std::vector<RigidBody*>collisions;
	std::vector<RigidBody*>special_collisions;
};

} /* namespace physic */

#endif /* SOURCE_CLASS_PHYSIC_RIGIDBODYCONTROLLER_H_ */
