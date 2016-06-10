#include "class/game/ageOfCube/map/building/tower/MainTower.h"
#include "class/game/ageOfCube/map/building/tower/Tower.h"
#include "class/game/ageOfCube/map/Map.h"
#include "class/display/draw/drawObject/AllDrawObjects.h"
#include "class/display/light/LightControl.h"
#include "class/display/draw/Draw.h"
namespace AOC {
void MainTower::building_pre_init(){
	//std::cout<<"Tree::pre_init()"<<std::endl;
	tower_Drawobj=Display::AllDrawObjects::get_cur_object()->get("building/basic_cube_tower_1");
	//tower_Drawobj=Display::AllDrawObjects::get_cur_object()->get("building/ball_spawn_tower");

	timer=0;
	attack_cycle=60;
	//tree_Drawobj=AllDrawObjects::get_cur_object()->get("landscape/broadleaftree");
}
MainTower::MainTower() {
	tower_Drawobj=0;
	size = 9.0;
	timer=0;
	loop_time=200;
}
MainTower::MainTower(MainTower* tower){
	init(10000,0);
	tower_Drawobj=tower->tower_Drawobj;
	size=tower->size;
	timer=0;
	loop_time=tower->loop_time;
	attack_cycle=tower->attack_cycle;

}
MainTower::~MainTower() {

}
void MainTower::save_building(FILE * file){
	fprintf(file,"%d\n",timer);
}
void MainTower::load_building(FILE * file){
	fscanf(file,"%d\n",&timer);
}
void MainTower::building_set_pos(int x,int y,int z){
	math::vec3<int> real_size=get_cube_large_size();
	pos.set_pos(glm::vec3(AOC::Map::CUBE_SIZE*x+0.5*real_size.x,
			AOC::Map::CUBE_SIZE*y+0.5*real_size.y,
			AOC::Map::CUBE_SIZE*z+0.5*real_size.z));
	pos.set_scale(glm::vec3(size,size,size));
}
void MainTower::building_update(){
	attack_update();
	//std::cout<<"MainTower::building_update() attack cycle="<<attack_cycle<<std::endl;
	if(timer<loop_time){
		timer++;
		//hp_alter(-1);
	}else{
		timer=0;
	}
}
void MainTower::draw_building(){

	float light_val=sqrt(fabs(((float)timer/(float)loop_time)-0.5));
	math::vec3<int> real_size=get_cube_large_size();
	Display::PointLight *light=new Display::PointLight(
			glm::vec3(AOC::Map::CUBE_SIZE*x+0.5*real_size.x,
			AOC::Map::CUBE_SIZE*y+1.4*real_size.y,
			AOC::Map::CUBE_SIZE*z+0.5*real_size.z),
			glm::vec3(50*light_val,50*light_val,50*light_val),false);
	Display::Draw::get_cur_object()->lightControl->push_temp_light(light);
	tower_Drawobj->push_temp_drawdata(new Display::DrawDataObj(&pos));

}
} /* namespace AOC */
