#include "class/display/draw/drawObject/drawData/DrawDataObj.h"
namespace Display{
DrawDataObj::DrawDataObj() {
	pos=0;
	draw_shadow=false;
	delete_pos=false;
}
DrawDataObj::DrawDataObj(math::Position* _pos,bool _draw_shadow,bool _delete_pos) {
	set_pos(_pos);
	draw_shadow=_draw_shadow;
	delete_pos=_delete_pos;
}
DrawDataObj::~DrawDataObj() {
	if(delete_pos)delete pos;
/*
 * don't delete pos!! handle by outside
 */
}
void DrawDataObj::set_pos(math::Position* _pos){
	pos=_pos;
}
}
