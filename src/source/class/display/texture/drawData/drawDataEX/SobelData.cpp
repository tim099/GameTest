#include "class/display/texture/drawData/drawDataEX/SobelData.h"
#include "class/display/shader/shader2D/Shader2D.h"
#include <iostream>
SobelData::SobelData(glm::vec2 _sobel_dv) {
	sobel_dv=_sobel_dv;
}
SobelData::~SobelData() {

}
void SobelData::prepare_to_draw(Shader *shader2D){
	shader2D->Enable(SobelMode);
	shader2D->sent_Uniform("sobel_dv",sobel_dv);
}
void SobelData::draw_end(Shader* shader2D){
	shader2D->Disable(SobelMode);
}

