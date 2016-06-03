#ifndef SOURCE_CLASS_DISPLAY_LIGHT_CUBELIGHT_H_
#define SOURCE_CLASS_DISPLAY_LIGHT_CUBELIGHT_H_
#include "glm/vec3.hpp"
namespace Display{
class CubeLight {
public:
	CubeLight();
	virtual ~CubeLight();
	glm::vec3 pos;
	glm::vec3 color;
	float size;
	glm::vec3 cube_size;
};
}
#endif /* SOURCE_CLASS_DISPLAY_LIGHT_CUBELIGHT_H_ */
