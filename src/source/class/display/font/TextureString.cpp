#include "class/display/font/TextureString.h"
#include "class/display/font/DrawDataStr.h"
#include "class/display/font/StringRenderer.h"
namespace Display{
TextureString::TextureString() {

}
TextureString::~TextureString() {

}
void TextureString::draw(Shader2D* shader2D,DrawData *data){
	DrawDataStr* data_str=(DrawDataStr*)data;//no need to delete handle by outside
	data_str->strRenderer->draw_string(shader2D,data_str->renderStr);
	//delete data_str;//test
}
}
