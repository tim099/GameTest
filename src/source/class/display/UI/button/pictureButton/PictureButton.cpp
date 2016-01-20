#include "class/display/UI/button/pictureButton/PictureButton.h"
#include "class/display/draw/texture/DrawTexture.h"
#include "class/display/texture/texture2D/DrawData2D.h"
#include "class/display/texture/drawData/drawDataEX/SobelData.h"
#include "class/display/texture/drawData/drawDataEX/ColorAlter.h"
#include "class/display/window/ViewPort.h"
#include "class/display/draw/Draw.h"
#include "class/display/font/RenderString.h"
#include <iostream>
namespace UI {

PictureButton::PictureButton(glm::vec2 _pos,Texture* _tex2D,double width,double _height){
	height=_height;
	str_size=0;
	glm::vec2 but_size=glm::vec2(width,width/(_tex2D->get_aspect()/ViewPort::get_cur_viewport_aspect()));
	if(height!=AutoHeight){
		but_size.y*=height;
	}
	initial(_pos,but_size);
	tex2D=_tex2D;
	str=0;
}
PictureButton::~PictureButton() {
	if(str)delete str;
}
void PictureButton::set_string(std::string* _str,double _str_size){
	if(str)delete str;
	str=_str;
	str_size=_str_size;
	if(str_size==auto_stringSize){
		str_size=1.0;
		RenderString* rstr=new RenderString(*str,str_size,get_middle_pos(),true);
		glm::vec2 strsize=rstr->string_size();
		double alter=1.0;
		static const float edgex=0.9,edgey=0.9;
		if(strsize.x>edgex*size.x){
			alter=(edgex*size.x/strsize.x);
		}
		if(strsize.y>edgey*0.5*size.y){
			if((edgey*0.5*size.y/strsize.y)<alter)alter=(edgey*0.5*size.y/strsize.y);
		}
		str_size=alter;
		delete rstr;
	}
}
void PictureButton::start_draw(Draw* draw){
    DrawData* data=new DrawData2D(1.0,pos,size.x,height);

    if(state==Selectable_on){
    	data->ex_datas.push_back(new ColorAlter(glm::vec3(0.3,0.3,0.3)));
        //data->ex_datas.push_back(new SobelData(glm::vec2(20,10)));
    }else if(state==Selectable_selected){
        //data->ex_datas.push_back(new SobelData(glm::vec2(20,10)));
        data->ex_datas.push_back(new ColorAlter(glm::vec3(0.7,0.7,0.7)));
    }
    draw->push(new DrawTexture(tex2D,data));
    if(str){
    	draw->push(new RenderString(*str,str_size,get_middle_pos(),true));
    }
}
} /* namespace UI */
