#include "class/display/draw/object/drawData/DrawDataObj.h"

DrawDataObj::DrawDataObj() {
	pos=0;
	draw_shadow=false;
}
DrawDataObj::DrawDataObj(Position* _pos,bool _draw_shadow) {
	set_pos(_pos);
	draw_shadow=_draw_shadow;
}
DrawDataObj::~DrawDataObj() {
/*
 * don't delete pos!! handle by outside
 */
}
void DrawDataObj::set_pos(Position* _pos){
	pos=_pos;
}
