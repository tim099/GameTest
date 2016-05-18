#ifndef SOURCE_CLASS_PHYSIC_RIGIDBODY_H_
#define SOURCE_CLASS_PHYSIC_RIGIDBODY_H_
#include "class/tim/math/vec3.h"
namespace physic {

class RigidBody {
public:
	RigidBody();
	virtual ~RigidBody();

	double size;
	math::vec3<double> vel;
	math::vec3<double> pos;
};

} /* namespace physic */

#endif /* SOURCE_CLASS_PHYSIC_RIGIDBODY_H_ */
