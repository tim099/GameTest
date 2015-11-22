#include "class/game/map/TaskCreateMapModel.h"
#include "class/game/map/DisplayMap.h"
#include <iostream>
TaskCreateMapModel::TaskCreateMapModel(DisplayMap* _dmap,int _px,int _pz) {
	px=_px;
	pz=_pz;
	dmap=_dmap;
	mapmodel=0;
}
TaskCreateMapModel::~TaskCreateMapModel() {

}
void TaskCreateMapModel::ExecuteTask(){
	mapmodel=dmap->create_map_model(px,pz);
	//dmap->create_map_object(px,pz,mapmodel);
}
