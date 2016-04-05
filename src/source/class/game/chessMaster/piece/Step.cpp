#include "class/game/chessMaster/piece/Step.h"

namespace CM {

Step::Step(int _x,int _y,int _nx,int _ny,int _score) {
	x=_x,y=_y,nx=_nx,ny=_ny;score=_score;ntype=0;
}
Step::Step(Step *step){
	x=step->x,y=step->y,nx=step->nx,ny=step->ny;score=step->score;ntype=step->ntype;
}
Step::~Step() {

}
Step& Step::operator=(const Step& step){
	x=step.x,y=step.y,nx=step.nx,ny=step.ny;score=step.score;ntype=step.ntype;
	return (*this);
}
} /* namespace CM */
