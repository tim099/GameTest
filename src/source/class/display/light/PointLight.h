#ifndef POINTLIGHT_H_
#define POINTLIGHT_H_
#include "glm/glm.hpp"
#include "class/display/light/Light.h"
namespace Display{
class PointLight : public Display::Light{
public:
	PointLight(glm::vec3 pos,glm::vec3 color,bool shadow);
	virtual ~PointLight();
	glm::mat4 get_LVP(float aspect,int n)const;
	glm::vec3 pos;
	glm::vec3 color;
protected:

};
}
#endif /* POINTLIGHT_H_ */
