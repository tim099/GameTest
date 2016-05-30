#include "class/display/texture/texture2D/drawDataEX/SobelData.h"
#include "class/display/shader/shader2D/Shader2D.h"
#include <iostream>
namespace Display{
namespace drawDataEX{
SobelData::SobelData(float _sobel_dvx,float _sobel_dvy) {
	sobel_dvx=_sobel_dvx;
	sobel_dvy=_sobel_dvy;
}
SobelData::~SobelData() {

}
void SobelData::prepare_to_draw(Shader *shader2D){
	shader2D->Enable(Shader::SobelMode);
	shader2D->sent_Uniform("sobel_dv",sobel_dvx,sobel_dvy);
}
void SobelData::draw_end(Shader* shader2D){
	shader2D->Disable(Shader::SobelMode);
}
}
}
