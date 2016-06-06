#include "class/game/ageOfCube/map/minion/ball/Ball.h"
#include "class/display/draw/Draw.h"
#include "class/display/draw/drawObject/AllDrawObjects.h"
#include "class/game/ageOfCube/map/Map.h"
#include "class/game/ageOfCube/map/ai/search/Astar.h"

#include "class/game/ageOfCube/unit/UnitController.h"
namespace AOC {
void Ball::minion_pre_init(){
	ball_Drawobj=Display::AllDrawObjects::get_cur_object()->get("building/ball_spawn_tower_part_4");
}
Ball::Ball() {
	ball_Drawobj=0;
	stuck_timer=0;
	stuck_times=0;
	colli_timer=0;
	timer=0;
	finder=0;

	colli_sound.set_source("default_sound_effect/Blip_Select3.wav");
}
Ball::Ball(Ball* ball) {
	ball_Drawobj=ball->ball_Drawobj;
	stuck_timer=0;
	stuck_times=0;
	colli_timer=0;
	timer=0;
	finder=0;
	colli_sound.set_source("default_sound_effect/Blip_Select3.wav");
}
Ball::~Ball() {
	if(finder)delete finder;
}
void Ball::save_minion(FILE * file){
	fprintf(file,"%d\n",timer);
	if(finder&&finder->get()->find){
		AI::search::FindPath* path=dynamic_cast<AI::search::FindPath*>(finder->get());
		fprintf(file,"1\n");
		path->save(file);
	}else{
		fprintf(file,"0\n");
	}
}
void Ball::load_minion(FILE * file){
	fscanf(file,"%d\n",&timer);
	int flag;
	///*
	fscanf(file,"%d\n",&flag);
	if(flag){
		if(finder)delete finder;
		AI::search::FindPath* path=new AI::search::FindPath();
		path->load(file);
		finder=new Tim::SmartPointer<AI::search::Finder>(path);
		//finder->get()->find=true;
	}
	//*/
}
void Ball::minion_update(){

	ball_move();
	//if(rigid_body.be_collided||rigid_body.collided){
		//colli_sound.pause();
		//colli_sound.play();
	//}
	timer++;
	rigid_body.mass=rigid_body.radius*rigid_body.radius*rigid_body.radius;
	if(timer>2500)delete this;
	//set_position(get_position()+math::vec3<double>(0.05,0,0));
}
void Ball::find_path(){
	Unit* unit=UnitController::get_cur_object()->search_unit("MainTower",rigid_body.pos);
	if(unit){
		math::vec3<int>des(unit->get_mid_pos_int());
		//std::cout<<"get_pos_int():"<<des.x<<","<<des.y<<","<<des.z<<std::endl;
		AI::search::FindPath *find=new AI::search::FindPath(
				rigid_body.pos,2*rigid_body.radius,des,1);
		if(finder)delete finder;

		finder=new Tim::SmartPointer<AI::search::Finder>(find);
		finder->get()->max_search_times=40000;
		finder->get()->min_search_times=5000;
		AI::search::SearchTask *task=new AOC::AI::search::SearchTask(*finder);
		AI::search::Astar::get_cur_object()->push_task(task);
	}
}
void Ball::explode(){
	if(rigid_body.radius>0.45){
		if((rigid_body.be_collided&&rigid_body.be_collided->get_type()=="MapRigidBody")){

			for(int i=-2;i<=2;i++){
				for(int j=-2;j<=2;j++){
					for(int k=-2;k<=2;k++){
						Map::get_cur_object()->set_cube_type(
								rigid_body.pos.x/Map::CUBE_SIZE+i,
								rigid_body.pos.y/Map::CUBE_SIZE+j,
								rigid_body.pos.z/Map::CUBE_SIZE+k,
								Cube::cubeNull);
					}
				}
			}

			delete this;
		}
	}else{
		rigid_body.radius*=1.02;
	}
}
void Ball::moving(){
	AI::search::FindPath* path=dynamic_cast<AI::search::FindPath*>(finder->get());
	if(path&&path->cur_at<path->path.size()){
		if((get_pos()-(path->path.at(path->cur_at))).get_length()<0.5*Map::CUBE_SIZE){//reach!!
			path->cur_at++;
			stuck_timer=0;
		}
		if(path->cur_at<path->path.size()){
			if(rigid_body.collided){
				colli_timer=10;
			}
			if(colli_timer<=0){
				math::vec3<double> target=path->path.at(path->cur_at);
				move_to(target,0.025);
				stuck_timer++;
			}else{
				colli_timer--;
			}
		}else{
			if(finder)delete finder;
			finder=0;
			rigid_body.acc=math::vec3<double>(0,0,0);
			colli_sound.play();
			delete this;
		}
	}else{
		//explode();
	}
}
void Ball::ball_move(){
	if(stuck_timer>100){
		stuck_times++;
		stuck_timer=0;
		if(stuck_times<2){
			find_path();
		}else{
			if(finder&&finder->get()->search_done){
				delete finder;
				finder=0;
			}

		}
		//std::cout<<"ball stuck"<<std::endl;

	}
	if(timer==50){
		//std::cout<<"Ball::minion_update() find path timer="<<timer<<std::endl;
		find_path();
		//std::cout<<"Ball::minion_update() find path end"<<std::endl;
	}

	if(finder&&(*finder)->search_done){
		if((*finder)->find){
			moving();
		}else{
			if(finder&&finder->get()->search_done){
				delete finder;
				finder=0;
			}
		}

	}else{
		rigid_body.vel.y-=0.003f;
	}
}
void Ball::draw_minion(){
	math::vec3<double> pos=get_pos();
	dp_pos.set_pos(glm::vec3(pos.x,pos.y,pos.z));
	dp_pos.set_scale(glm::vec3(2.0*rigid_body.radius,2.0*rigid_body.radius,2.0*rigid_body.radius));
	ball_Drawobj->push_temp_drawdata(new Display::DrawDataObj(&dp_pos));
}
} /* namespace AOC */
