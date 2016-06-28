#ifndef PARALLELLIGHT_H_
#define PARALLELLIGHT_H_
#include "glm/glm.hpp"
#include "class/display/light/Light.h"
#include "class/tim/geometry/3D/AABB.h"

namespace Display{
class ParallelLight : public Display::Light{
public:
	ParallelLight(glm::vec3 vec,glm::vec3 color,bool shadow);
	virtual ~ParallelLight();
	glm::mat4 get_LVP(float aspect,double size,glm::vec3 trans)const;
	glm::mat4 get_PSSM_LVP(float aspect, double size, glm::vec3 trans, Tim::AABB PSSM_AABB);
	glm::vec3 vec;
	glm::vec3 color;
protected:

};
}
#endif /* PARALLELLIGHT_H_ */
