#ifndef DRAWDATA2D_H_
#define DRAWDATA2D_H_
#include "class/display/texture/drawData/DrawData.h"
class DrawData2D : public DrawData{
public:
	/*targetaspect is the aspect of render target(window or FBO,aspect=width/height
	 *
	 *
	 */
	DrawData2D(double _targetaspect=1.0,float _alpha=1.0,
			glm::vec2 _pos=glm::vec2(0,1.0),float _width=1.0);//pos is the position to render texture form 0,0 ot 1,1
	virtual ~DrawData2D();

	double targetaspect;
	glm::vec2 pos;
	float alpha;
	float width;
};

#endif /* DRAWDATA2D_H_ */
