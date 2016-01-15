#ifndef POSITION_H_
#define POSITION_H_
#include <GL/glew.h>
#include <glm/glm.hpp>
class Position {
public:
	Position();
	Position(const Position &p);
	Position(glm::vec3 pos,glm::vec3 r,Position *parent_pos=0);
	virtual ~Position();


	void initialize(const Position &p);
	void initialize(glm::vec3 pos,glm::vec3 r,Position *parent_pos);
	glm::mat4 PosMat()const;

	Position *parent_pos;
	glm::vec3 pos;
	glm::vec3 r;
};

#endif /* POSITION_H_ */
