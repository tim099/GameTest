#ifndef LINE2D_H_
#define LINE2D_H_
#include "class/tim/geometry/2D/Geometry2D.h"
namespace Tim {

class Line2D {
public:
	Line2D(glm::vec2 vec,glm::vec2 pos);
	virtual ~Line2D();

	glm::vec2 vec;
	glm::vec2 pos;
};

} /* namespace Tim */

#endif /* LINE2D_H_ */
