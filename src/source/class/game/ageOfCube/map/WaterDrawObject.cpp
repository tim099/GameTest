#include "class/game/ageOfCube/map/WaterDrawObject.h"
#include "class/display/model/Model.h"

WaterDrawObject::WaterDrawObject() {
 init();
}
void WaterDrawObject::init(){
	init_drawObject("","","",false);
	mat=math::vec4<float>(0.3,0.9,0.13,0.15);

	alpha_drawobject=true;
}
WaterDrawObject::~WaterDrawObject() {

}
