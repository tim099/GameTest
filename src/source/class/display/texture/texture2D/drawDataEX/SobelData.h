#ifndef SOBELDATA_H_
#define SOBELDATA_H_
//#include <glm/glm.hpp>
#include "class/display/draw/drawData/DrawDataEX/DrawDataEX.h"
namespace Display{
namespace drawDataEX{
class SobelData : public DrawDataEX{
public:
	SobelData(float sobel_dvx,float sobel_dvy);
	virtual ~SobelData();
	virtual void prepare_to_draw(Shader* shader2D);
	virtual void draw_end(Shader* shader2D);
	float sobel_dvx;
	float sobel_dvy;
};
}
}
#endif /* SOBELDATA_H_ */
