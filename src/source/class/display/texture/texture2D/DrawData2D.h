#ifndef DRAWDATA2D_H_
#define DRAWDATA2D_H_
#include "class/display/texture/drawData/DrawData.h"
class DrawData2D : public DrawData{
public:
	DrawData2D(double _targetaspect=1.0,float _alpha=1.0,
			glm::vec2 _pos=glm::vec2(0,1.0),float _size=1.0);
	virtual ~DrawData2D();
	double targetaspect;
	float alpha;
	glm::vec2 pos;
	float size;
};

#endif /* DRAWDATA2D_H_ */
