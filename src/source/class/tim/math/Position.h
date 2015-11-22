#ifndef POSITION_H_
#define POSITION_H_
#include <GL/glew.h>
#include <glm/glm.hpp>
class Position {
public:
	Position(const Position &p);
	Position(glm::vec3 pos,glm::vec3 r,Position *parent_pos=0);
	virtual ~Position();

	glm::mat4 PosMat()const;
	void initialize(glm::vec3 pos,glm::vec3 r,Position *parent_pos);
	Position *parent_pos;
	glm::vec3 pos;
	glm::vec3 r;
};

#endif /* POSITION_H_ */
