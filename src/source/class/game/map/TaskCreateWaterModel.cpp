#include "class/game/map/TaskCreateWaterModel.h"
#include "class/game/map/DisplayMap.h"
TaskCreateWaterModel::TaskCreateWaterModel(DisplayMap* _dmap,int _px,int _pz) {
	px=_px;
	pz=_pz;
	dmap=_dmap;
}

TaskCreateWaterModel::~TaskCreateWaterModel() {

}

void TaskCreateWaterModel::ExecuteTask(){
	dmap->create_water_object(px,pz);
}
