#ifndef SOBELDATA_H_
#define SOBELDATA_H_
#include <glm/glm.hpp>
#include "class/display/texture/drawData/DrawDataEX/DrawDataEX.h"
class SobelData : public DrawDataEX{
public:
	SobelData(glm::vec2 sobel_dv);
	virtual ~SobelData();
	virtual void prepare_to_draw(Shader* shader2D);
	virtual void draw_end(Shader* shader2D);
	glm::vec2 sobel_dv;
};

#endif /* SOBELDATA_H_ */
