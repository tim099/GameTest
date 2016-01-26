#ifndef DRAWDATA_H_
#define DRAWDATA_H_
#include "class/display/draw/drawData/DrawDataEX/DrawDataEX.h"
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>
class Shader;
class DrawData {
public:
	DrawData();
	virtual ~DrawData();
	/*
	 * sent data to shader before draw
	 */
	void prepare_to_draw(Shader* shader);
	/*
	 * clear sent data in shader
	 */
	void draw_end(Shader* shader);
	std::vector<DrawDataEX*>ex_datas;
};

#endif /* DRAWDATA_H_ */
