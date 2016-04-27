#include "class/display/font/DrawDataStr.h"
#include "class/display/font/RenderString.h"
#include <iostream>
namespace Display{
DrawDataStr::DrawDataStr(StringRenderer* _strRenderer,RenderString* _renderStr) {
	strRenderer=_strRenderer;
	renderStr=_renderStr;
}
DrawDataStr::~DrawDataStr() {
	//std::cout<<"delete DrawDataStr"<<std::endl;
	delete renderStr;
}
}
