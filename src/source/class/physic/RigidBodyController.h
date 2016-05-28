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
	void push(RigidBody* rigid_body){
		rigid_bodys.push_back(rigid_body);
	}
	void remove(RigidBody* rigid_body){
		for(unsigned i=0;i<rigid_bodys.size();i++){
			if(rigid_bodys.at(i)==rigid_body){
				rigid_bodys.at(i)=rigid_bodys.back();
				rigid_bodys.pop_back();
			}
		}
	}
	virtual void update();
protected:
	void check_collision();
	void check_collision(RigidBody* rigid_body);
	std::vector<RigidBody*>rigid_bodys;
	std::vector<RigidBody*>collisions;
	std::vector<RigidBody*>special_collisions;
};

} /* namespace physic */

#endif /* SOURCE_CLASS_PHYSIC_RIGIDBODYCONTROLLER_H_ */
