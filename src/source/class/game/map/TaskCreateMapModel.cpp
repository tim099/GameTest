#include "class/game/map/TaskCreateMapModel.h"
#include "class/game/map/DisplayMap.h"
#include <iostream>
TaskCreateMapModel::TaskCreateMapModel(DisplayMap* _dmap,int _px,int _pz) {
	px=_px;
	pz=_pz;
	dmap=_dmap;
}
TaskCreateMapModel::~TaskCreateMapModel() {

}
void TaskCreateMapModel::ExecuteTask(){
	dmap->create_map_object(px,pz);
}
