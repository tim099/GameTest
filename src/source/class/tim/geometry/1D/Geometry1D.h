#ifndef GEOMETRY1D_H_
#define GEOMETRY1D_H_
#include "class/tim/math/Math.h"
namespace Tim {

class Geometry1D {
public:
	Geometry1D();
	virtual ~Geometry1D();
	/*
	 *detect 1D line coincide with a dot if coincide return ture otherwise return false
	 */
	static bool between(glm::vec2 line,float dot);
	/*
	 *detect 1D lines coincide if coincide return ture otherwise return false
	 */
	static bool coincide(glm::vec2 line_a,glm::vec2 line_b);
};

} /* namespace Tim */

#endif /* GEOMETRY1D_H_ */
