#include "class/display/texture/texture2D/drawDataEX/ColorAlter.h"
#include "class/display/shader/shader2D/Shader2D.h"
namespace Display{
namespace drawDataEX{
ColorAlter::ColorAlter(glm::vec3 _alter_value) {
	alter_value=_alter_value;
}
ColorAlter::~ColorAlter() {

}
void ColorAlter::prepare_to_draw(Shader *shader2D){
	shader2D->Enable(Shader::ColorAlterMode);
	shader2D->sent_Uniform("alter_value",alter_value);
}
void ColorAlter::draw_end(Shader* shader2D){
	shader2D->Disable(Shader::ColorAlterMode);
}
}
}
