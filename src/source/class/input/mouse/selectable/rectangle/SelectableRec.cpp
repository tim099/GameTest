#include "class/input/mouse/selectable/rectangle/SelectableRec.h"
#include "class/tim/geometry/2D/RectP2D.h"
#include "class/input/mouse/Mouse.h"
SelectableRec::SelectableRec() {

}
SelectableRec::~SelectableRec() {

}
bool SelectableRec::detect_mouse_collision(Mouse *mou){
	glm::vec2 pos=get_rec_pos();
	glm::vec2 size=get_rec_size();
	return Tim::RectP2D::coincide(mou->get_tex_space_pos(),pos,pos+glm::vec2(size.x,-size.y));
}
