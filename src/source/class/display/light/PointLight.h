#ifndef POINTLIGHT_H_
#define POINTLIGHT_H_
#include <class/display/light/Light.h>
class PointLight : public Light{
public:
	PointLight(glm::vec3 pos,glm::vec3 color,bool shadow);
	virtual ~PointLight();
	glm::mat4 sent_uniform(GLuint programID,float aspect,int n);
	glm::mat4 get_LVP(float aspect,int n)const;
	glm::vec3 pos;
	glm::vec3 color;
protected:

};

#endif /* POINTLIGHT_H_ */
