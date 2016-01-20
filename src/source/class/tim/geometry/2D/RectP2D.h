#ifndef RECTP2D_H_
#define RECTP2D_H_
/*Rect(angle) P(arallel to x,y axis) 2D(in 2D dimension)
 * 2D Rectangle that all lines parallel with x and y axis
 *
 */
#include "class/tim/geometry/2D/Geometry2D.h"
#include "class/tim/geometry/1D/Geometry1D.h"
namespace Tim {

class RectP2D {
public:
	/* a is the left down corner of the rectangle
	 * for all a,a.x<b.x and a.y<b.y
	 */
	RectP2D(glm::vec2 a,glm::vec2 b);
	virtual ~RectP2D();
	/*
	 * detect if the dot is coincide with this RectP2D
	 */
	bool coincide(glm::vec2 dot);
	static bool coincide(glm::vec2 dot,glm::vec2 a,glm::vec2 b);


	/*
	 * detect if another RectP2D is coincide with this RectP2D
	 */
	bool coincide(RectP2D *rec);
	/*
	 * return the size
	 */
	glm::vec2 get_size()const;
	glm::vec2 a,b;
};

} /* namespace Tim */

#endif /* RECTP2D_H_ */
