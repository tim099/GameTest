#include "class/display/font/RenderString.h"
#include "class/display/font/StringRenderer.h"
#include "class/display/window/ViewPort.h"
#include <iostream>
RenderString::RenderString(std::string _str,float _size,glm::vec2 _pos,bool _render_at_middle) {
	str=_str;
	size=_size;
	pos=_pos;
	render_at_middle=_render_at_middle;
}
RenderString::~RenderString() {
	//std::cout<<"delete STR:\n"<<str<<std::endl;
}
glm::vec2 RenderString::font_size()const{
	return glm::vec2(size*Font_Interval,size);
}
glm::vec2 RenderString::string_size()const{
	glm::vec2 f_size=font_size();
	char c;
	int line=0,col=0;
	int max_col=0;
	for (unsigned i = 0; i < str.size(); i++) {
		c = str.at(i);
		switch (c) {
		case '\n':
			line++;
			col = 0;
			break;
		case '	':
			col += StringRenderer::TAB_SIZE;
			break;
		default:
			col++;
		}
		if(col>max_col)max_col=col;
	}
	return glm::vec2(f_size.x*max_col,f_size.y*(line+1));
}
