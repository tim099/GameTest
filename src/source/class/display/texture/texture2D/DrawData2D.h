#ifndef DRAWDATA2D_H_
#define DRAWDATA2D_H_
#include "class/display/draw/drawData/DrawData.h"
namespace Display{
class DrawData2D: public DrawData {
public:
	static const float AutoHeight = 0.0f;
	/*targetaspect is the aspect of render target(window or FBO,aspect=width/height
	 *pos is the position to render texture form 0,0 ot 1,1
	 */
	DrawData2D(float _alpha = 1.0, glm::vec2 _pos = glm::vec2(0, 1.0),
			float width = 1.0f, float height = AutoHeight);

	virtual ~DrawData2D();

	glm::vec2 pos;
	float alpha;
	float width,height;
};
}
#endif /* DRAWDATA2D_H_ */
