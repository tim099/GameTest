#include "class/game/map/landscape/Landscape.h"
#include "class/game/map/landscape/tree/Tree.h"

bool Landscape::landscape_inited=false;

void  Landscape::Landscape_init(){
	if(landscape_inited)return;



	landscape_inited=true;
}
void Landscape::landscape_pre_init(){

}
Landscape::Landscape() {

}
Landscape::~Landscape() {

}

