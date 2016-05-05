#include "class/game/chessMaster/chessboard/StepData.h"

namespace CM {

StepData::StepData() {
	wins=0,simulations=0;
	//score=0,depth=0;
}
StepData::~StepData() {

}
void StepData::save(FILE * file){
	fprintf(file,"%d %d\n",wins,simulations);
	//fprintf(file,"%d %d\n",score,depth);
}
void StepData::load(FILE * file){
	fscanf(file,"%d %d\n",&wins,&simulations);
	//fscanf(file,"%d %d\n",&score,&depth);
}
} /* namespace CM */
