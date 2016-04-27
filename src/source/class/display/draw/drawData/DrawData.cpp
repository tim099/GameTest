#include "class/display/draw/drawData/DrawData.h"
#include "class/display/shader/Shader.h"
#include <iostream>
namespace Display{
DrawData::DrawData() {

}
DrawData::~DrawData() {
	for(unsigned i=0;i<ex_datas.size();i++){
		delete ex_datas.at(i);
	}
}
void DrawData::prepare_to_draw(Shader *shader){
	for(unsigned i=0;i<ex_datas.size();i++){
		ex_datas.at(i)->prepare_to_draw(shader);
	}
}
void DrawData::draw_end(Shader *shader){
	for(unsigned i=0;i<ex_datas.size();i++){
		ex_datas.at(i)->draw_end(shader);
	}
}
}
