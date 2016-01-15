#ifndef DRAWDATA_H_
#define DRAWDATA_H_
#include "class/display/texture/drawData/DrawDataEX/DrawDataEX.h"
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>
class Shader;
class DrawData {
public:
	DrawData();
	virtual ~DrawData();
	void prepare_to_draw(Shader* shader2D);
	void draw_end(Shader* shader2D);
	std::vector<DrawDataEX*>ex_datas;
};

#endif /* DRAWDATA_H_ */
