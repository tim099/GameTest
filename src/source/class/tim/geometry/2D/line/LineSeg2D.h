#ifndef LINESEG2D_H_
#define LINESEG2D_H_
#include "class/tim/geometry/2D/Geometry2D.h"
namespace Tim {

class LineSeg2D {
public:
	LineSeg2D(glm::vec2 a,glm::vec2 b);
	virtual ~LineSeg2D();
	glm::vec2 a,b;
};

} /* namespace Tim */

#endif /* LINESEG2D_H_ */
