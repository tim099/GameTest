/*
 * AABB.h
 *
 *  Created on: 2016¦~6¤ë27¤é
 *      Author: LukeWu
 */

#ifndef SOURCE_CLASS_TIM_GEOMETRY_3D_AABB_H_
#define SOURCE_CLASS_TIM_GEOMETRY_3D_AABB_H_

#include "class/tim/math/Math.h"

namespace Tim {

class AABB {
public:
	AABB(glm::vec3 _max_pos, glm::vec3 _min_pos);
	virtual ~AABB();

	glm::vec3 max_pos;
	glm::vec3 min_pos;
};

} /* namespace Tim */

#endif /* SOURCE_CLASS_TIM_GEOMETRY_3D_AABB_H_ */
