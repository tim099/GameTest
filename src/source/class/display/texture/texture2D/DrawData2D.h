#ifndef DRAWDATA2D_H_
#define DRAWDATA2D_H_
#include "class/display/draw/drawData/DrawData.h"
#include "class/tim/math/vec2.h"
namespace Display{

class DrawData2D: public DrawData {
public:
	static const float AutoHeight = 0.0f;
	/*targetaspect is the aspect of render target(window or FBO,aspect=width/height
	 *pos is the position to render texture form 0,0 ot 1,1
	 */
	DrawData2D(float _alpha = 1.0, math::vec2<float> _pos = math::vec2<float>(0.0f, 1.0f),
			float width = 1.0f, float height = AutoHeight);

	virtual ~DrawData2D();

	math::vec2<float> pos;
	float alpha;
	float width,height;
};
}
#endif /* DRAWDATA2D_H_ */
