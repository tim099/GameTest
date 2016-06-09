#include "class/game/entity/EntityPointer.h"
#include "class/game/entity/EntityController.h"
namespace entity {

EntityPointer::EntityPointer() {
	id=0;
}
EntityPointer::~EntityPointer() {

}
Entity* EntityPointer::get_entity(unsigned id){
	return EntityController::get_cur_object()->get_entity(id);
}
Entity* EntityPointer::get_entity()const{
	return get_entity(id);
}
} /* namespace entity */
