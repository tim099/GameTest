#include "class/game/ageOfCube/map/minion/ball/Ball.h"
#include "class/display/draw/Draw.h"
#include "class/display/draw/drawObject/AllDrawObjects.h"
#include "class/game/ageOfCube/map/Map.h"
namespace AOC {
void Ball::minion_pre_init(){
	ball_Drawobj=Display::AllDrawObjects::get_cur_object()->get("building/ball_spawn_tower_part_4");
}
Ball::Ball() {
	ball_Drawobj=0;
	timer=0;
}
Ball::Ball(Ball* ball) {
	ball_Drawobj=ball->ball_Drawobj;
	timer=0;
}
Ball::~Ball() {

}
void Ball::save_minion(FILE * file){
	fprintf(file,"%d\n",timer);
}
void Ball::load_minion(FILE * file){
	fscanf(file,"%d\n",&timer);
}
void Ball::minion_update(){
	//rigid_body.vel.x=-0.04f;
	rigid_body.vel+=0.0001*math::vec3<double>::normalize(rigid_body.vel);
	rigid_body.vel.y-=0.002f;
	timer++;
	if(timer<500){

	}else{
		/*
		if(rigid_body.radius>0.75){
			if((rigid_body.be_collided&&rigid_body.be_collided->get_type()=="MapRigidBody")){
				for(int i=-2;i<=2;i++){
					for(int j=-2;j<=2;j++){
						for(int k=-2;k<=2;k++){
							Map::get_cur_object()->set_cube_type(rigid_body.pos.x/Map::CUBE_SIZE+i,
																 rigid_body.pos.y/Map::CUBE_SIZE+j,
																 rigid_body.pos.z/Map::CUBE_SIZE+k,
																 Cube::cubeNull);
						}
					}
				}
				delete this;
			}
		}else{
			rigid_body.radius*=1.01;
		}
		*/
	}
	rigid_body.mass=rigid_body.radius*rigid_body.radius*rigid_body.radius;
	if(timer>800)delete this;
	//set_position(get_position()+math::vec3<double>(0.05,0,0));
}
void Ball::draw_minion(){
	math::vec3<double> pos=get_position();
	dp_pos.set_pos(glm::vec3(pos.x,pos.y,pos.z));
	dp_pos.set_scale(glm::vec3(2.0*rigid_body.radius,2.0*rigid_body.radius,2.0*rigid_body.radius));
	ball_Drawobj->push_temp_drawdata(new Display::DrawDataObj(&dp_pos));
}
} /* namespace AOC */
