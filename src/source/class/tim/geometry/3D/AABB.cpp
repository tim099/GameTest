/*
 * AABB.cpp
 *
 *  Created on: 2016¦~6¤ë27¤é
 *      Author: LukeWu
 */

#include "class/tim/geometry/3D/AABB.h"

namespace Tim {

AABB::AABB(glm::vec3 _max_pos, glm::vec3 _min_pos) {
	max_pos = _max_pos;
	min_pos = _min_pos;
}

AABB::~AABB() {
	// TODO Auto-generated destructor stub
}

} /* namespace Tim */
