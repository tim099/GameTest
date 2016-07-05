#include "class/game/ageOfCube/map/building/tower/BallSpawnTower.h"
#include "class/game/ageOfCube/map/Map.h"
#include "class/display/draw/drawObject/AllDrawObjects.h"
#include "class/display/light/LightControl.h"
#include "class/display/draw/Draw.h"
#include "class/game/ageOfCube/map/minion/MinionCreator.h"
#include <cstdio>
#include <iostream>
#include <cmath>
namespace AOC {
void BallSpawnTower::building_pre_init(){
	//std::cout<<"Tree::pre_init()"<<std::endl;
	tower_Drawobj=Display::AllDrawObjects::get_cur_object()->get("building/ball_spawn_tower");
	tower_part1=Display::AllDrawObjects::get_cur_object()->get("building/ball_spawn_tower_part_1");
	tower_part2=Display::AllDrawObjects::get_cur_object()->get("building/ball_spawn_tower_part_2");
	tower_part3=Display::AllDrawObjects::get_cur_object()->get("building/ball_spawn_tower_part_3");
	tower_part4=Display::AllDrawObjects::get_cur_object()->get("building/ball_spawn_tower_part_4");
	//tree_Drawobj=AllDrawObjects::get_cur_object()->get("landscape/broadleaftree");
}
BallSpawnTower::BallSpawnTower() {
	tower_Drawobj=0;
	tower_part1=0;
	tower_part2=0;
	tower_part3=0;
	tower_part4=0;
	timer=0;
	size = 2.0;
	loop_time=1600;
	loop_count=0;
	init_BallSpawnTower();
}
BallSpawnTower::BallSpawnTower(BallSpawnTower* tower) {
	init(100000,1);
	tower_Drawobj=tower->tower_Drawobj;
	tower_part1=tower->tower_part1;
	tower_part2=tower->tower_part2;
	tower_part3=tower->tower_part3;
	tower_part4=tower->tower_part4;
	timer=0;
	size = tower->size;
	loop_count=0;
	loop_time=tower->loop_time;
	init_BallSpawnTower();
}
BallSpawnTower::~BallSpawnTower() {

}
void BallSpawnTower::init_BallSpawnTower(){
	part0_pos.set_parent(&pos);
	part1_pos1.set_parent(&pos);
	part1_pos2.set_parent(&pos);
	part2_pos.set_parent(&pos);
	part3_pos.set_parent(&pos);
	part4_pos.set_parent(&pos);
	ball1.set_parent(&part4_pos);
	ball2.set_parent(&part4_pos);
	ball3.set_parent(&pos);
	ball4.set_parent(&pos);
}
void BallSpawnTower::save_building(FILE * file){
	fprintf(file,"%d %d %d\n",timer,loop_count,loop_time);
}
void BallSpawnTower::load_building(FILE * file){
	fscanf(file,"%d %d %d\n",&timer,&loop_count,&loop_time);
	loop_count=0;
}
void BallSpawnTower::building_set_pos(int x,int y,int z){
	math::vec3<int> real_size=get_cube_large_size();
	pos.set_pos(glm::vec3(AOC::Map::CUBE_SIZE*x+0.5*real_size.x,
			AOC::Map::CUBE_SIZE*y+0.5*real_size.y,
			AOC::Map::CUBE_SIZE*z+0.5*real_size.z));
	pos.set_scale(glm::vec3(0.9*size,0.9*size,0.9*size));
	part1_pos1.set_pos(glm::vec3(-0.376,0.02,0.188));
	part1_pos2.set_pos(glm::vec3(-0.376,0.02,-0.188));
	part1_pos1.set_scale(glm::vec3(0.5,0.5,0.5));
	part1_pos2.set_scale(glm::vec3(0.5,0.5,0.5));
	part2_pos.set_pos(glm::vec3(0.2,0,0));
	part2_pos.set_scale(glm::vec3(0.75,0.75,0.75));
	part3_pos.set_scale(glm::vec3(0.28,0.28,0.28));
	part3_pos.set_pos(glm::vec3(0.2,0.4,0));

	part4_pos.set_pos(glm::vec3(0.2,0,0));

	ball1.set_pos(glm::vec3(0.0,0.4,0));
	ball1.set_scale(glm::vec3(0.18,0.18,0.18));
	ball2.set_pos(glm::vec3(0.4*-cosf(M_PI/4.0),0.4*sinf(M_PI/4.0),0));
	ball2.set_scale(glm::vec3(0.18,0.18,0.18));
	ball3.set_scale(glm::vec3(0.18,0.18,0.18));
	ball4.set_scale(glm::vec3(0.18,0.18,0.18));
}
void BallSpawnTower::spawn(){
	Minion* ball=MinionCreator::get_cur_object()->create("Ball");
	math::vec3<double> recruit_pos(x*Map::CUBE_SIZE-0.15*size,
			  y*Map::CUBE_SIZE+0.093*size,
			  z*Map::CUBE_SIZE+0.5*size);
	math::vec3<double> relative_pos=recruit_pos-math::vec3<double>(pos.get_pos().x,
			pos.get_pos().y,pos.get_pos().z);

	relative_pos.rotate_by_y(90.0*get_rotate_int());
	ball->set_pos(math::vec3<double>(pos.get_pos().x+relative_pos.x,
			pos.get_pos().y+relative_pos.y,
			pos.get_pos().z+relative_pos.z));
	ball->set_vel((200.0/loop_time)*0.02*size*
			math::vec3<double>::normalize(
			math::vec3<double>(relative_pos.x,0,relative_pos.z)));



	ball->max_hp_alter(loop_count*10);
	ball->upgrade("fire",loop_count);

	double ball_size=0.16f*size*sqrt(ball->get_hp()/100.0);
	if(ball_size>0.9)ball_size=0.9;
	ball->set_size(ball_size);
	ball->set_player(get_player());
	ball->create_minion();

}
void BallSpawnTower::building_update(){
	if((timer)%(loop_time/8)==(loop_time/8)-1){
		spawn();
		//std::cout<<"BallSpawnTower::building_update() recruit"<<std::endl;
	}
	if(timer<loop_time){
		timer++;
	}else{
		timer=0;
		if(loop_time>400){
			loop_time*=0.95;
		}
		loop_count++;
	}
}
void BallSpawnTower::draw_building(){
	float light_val=sqrt(fabs(((float)((8*timer)%loop_time)/(float)loop_time)-0.5));
	math::vec3<int> real_size=get_cube_large_size();
	Display::PointLight *light=new Display::PointLight(
			glm::vec3(AOC::Map::CUBE_SIZE*x+0.5*real_size.x,
			AOC::Map::CUBE_SIZE*y+1.4*real_size.y,
			AOC::Map::CUBE_SIZE*z+0.5*real_size.z),
			glm::vec3(50*light_val,10*light_val,10*light_val),false);
	Display::Draw::get_cur_object()->lightControl->push_temp_light(light);
	tower_Drawobj->push_temp_drawdata(new Display::DrawDataObj(&part0_pos));

	part1_pos1.set_r(glm::vec3(0,2*360*((double)timer/loop_time-1.0/16),0));
	part1_pos2.set_r(glm::vec3(0,2*-360*((double)timer/loop_time-1.0/16),0));
	tower_part1->push_temp_drawdata(new Display::DrawDataObj(&part1_pos1));
	tower_part1->push_temp_drawdata(new Display::DrawDataObj(&part1_pos2));

	part2_pos.set_r(glm::vec3(0,0,360*((double)timer/loop_time)));
	tower_part2->push_temp_drawdata(new Display::DrawDataObj(&part2_pos));
	float y_val=sqrt(fabs(((float)((8*timer+loop_time/2)%loop_time)/(float)loop_time)-0.5));
	part3_pos.set_pos(glm::vec3(0.2,
			(0.25+0.2*y_val)*2,
			0));
	tower_part3->push_temp_drawdata(new Display::DrawDataObj(&part3_pos));
	float x_val=((float)((8*timer)%loop_time)/(float)loop_time);
	part4_pos.set_r(glm::vec3(0,0,45*((double)((8*timer)%loop_time)/loop_time)));
	ball3.set_pos(glm::vec3(-0.2-0.28*x_val,0,0));
	ball4.set_pos(glm::vec3(-0.48-0.24*x_val,-0.491*x_val*x_val,0));
	tower_part4->push_temp_drawdata(new Display::DrawDataObj(&ball1));
	tower_part4->push_temp_drawdata(new Display::DrawDataObj(&ball2));
	tower_part4->push_temp_drawdata(new Display::DrawDataObj(&ball3));
	tower_part4->push_temp_drawdata(new Display::DrawDataObj(&ball4));
}
} /* namespace AOC */
