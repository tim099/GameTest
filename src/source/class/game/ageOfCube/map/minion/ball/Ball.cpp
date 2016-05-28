#include "class/game/ageOfCube/map/minion/ball/Ball.h"
#include "class/display/draw/Draw.h"
#include "class/display/draw/drawObject/AllDrawObjects.h"
namespace AOC {
void Ball::minion_pre_init(){
	ball_Drawobj=Display::AllDrawObjects::get_cur_object()->get("building/ball_spawn_tower_part_4");
}
Ball::Ball() {
	ball_Drawobj=0;
}
Ball::Ball(Ball* ball) {
	ball_Drawobj=ball->ball_Drawobj;
}
Ball::~Ball() {

}
void Ball::minion_update(){
	rigid_body.vel.x=-0.02f;
	rigid_body.size=0.5f;
	rigid_body.set_detect_collision();
	//set_position(get_position()+math::vec3<double>(0.05,0,0));
}
void Ball::draw_minion(){
	math::vec3<double> pos=get_position();
	dp_pos.set_pos(glm::vec3(pos.x,pos.y,pos.z));
	dp_pos.set_scale(glm::vec3(rigid_body.size,rigid_body.size,rigid_body.size));
	ball_Drawobj->push_temp_drawdata(new Display::DrawDataObj(&dp_pos));
}
} /* namespace AOC */
