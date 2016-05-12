#ifndef DRAWDATA_H_
#define DRAWDATA_H_
#include "class/display/draw/drawData/drawDataEX/DrawDataEX.h"
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>
namespace Display{
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
	inline void push_ex_data(drawDataEX::DrawDataEX* data){
		ex_datas.push_back(data);
	}
	std::vector<drawDataEX::DrawDataEX*>ex_datas;
};
}
#endif /* DRAWDATA_H_ */
