#include "class/display/draw/drawObject/drawData/drawDateEX/SkyMap.h"
#include "class/display/shader/Shader.h"
namespace Display {
namespace drawDataEX {

SkyMap::SkyMap() {

}

SkyMap::~SkyMap() {

}
void SkyMap::prepare_to_draw(Shader* shader){
	shader->Enable(Display::Shader::SkyMap);
}
void SkyMap::draw_end(Shader* shader){
	shader->Disable(Display::Shader::SkyMap);
}
} /* namespace drawDataEX */
} /* namespace Display */
