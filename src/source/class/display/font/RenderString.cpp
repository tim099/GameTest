#include "class/display/font/RenderString.h"
#include "class/display/font/StringRenderer.h"
#include "class/display/window/ViewPort.h"
#include "class/tim/math/Math.h"
#include <iostream>
namespace Display{
RenderString::RenderString(std::string _str,float _size,
		math::vec2<float> _pos,
		bool _render_at_middle) {
	str=_str;
	size=_size;
	pos=_pos;
	render_at_middle=_render_at_middle;
	insert_at=-1;
}
RenderString::~RenderString() {
	//std::cout<<"delete STR:\n"<<str<<std::endl;
}
void RenderString::auto_char_size(math::vec2<float> max_size){
	math::vec2<float> strsize = string_size();
	strsize.y *= ViewPort::get_cur_window_aspect();
	size = Tim::Math::fit_in_maxsize(strsize, max_size);
}
math::vec2<float> RenderString::font_size()const{
	return math::vec2<float>(size*Font_Interval,size);
}
math::vec2<float> RenderString::string_size(const std::string *str,float size){
	math::vec2<float> f_size=font_size(size);
	char c;
	int line=0,col=0;
	int max_col=0;
	for (unsigned i = 0; i < str->size(); i++) {
		c = str->at(i);
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
	return math::vec2<float>(f_size.x*max_col,f_size.y*((line+1)));
}
math::vec2<float> RenderString::string_size()const{
	return string_size(&str,size);
}
}
