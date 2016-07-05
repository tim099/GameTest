#include "class/game/ageOfCube/map/minion/ball/Ball.h"
#include "class/display/draw/Draw.h"
#include "class/display/draw/drawObject/AllDrawObjects.h"
#include "class/game/ageOfCube/map/Map.h"
#include "class/game/ageOfCube/map/ai/search/Astar.h"
#include "class/game/ageOfCube/map/unit/UnitController.h"
#include "class/game/entity/EntityController.h"
#include "class/audio/AudioController.h"
#include "class/game/ageOfCube/map/attack/weapon/WeaponCreator.h"
#include "class/game/ageOfCube/player/PlayerController.h"
#include <cstdlib>
#include <ctime>
namespace AOC {
void Ball::minion_pre_init(){
	ball_Drawobj=Display::AllDrawObjects::get_cur_object()->get("minion/ball");
}
Ball::Ball() {
	ball_Drawobj=0;
	stuck_timer=0;
	stuck_times=0;
	colli_timer=0;
	timer=0;
	finder=0;
	set_max_hp(100);
}
Ball::Ball(Ball* ball) {
	ball_Drawobj=ball->ball_Drawobj;
	stuck_timer=0;
	stuck_times=0;
	colli_timer=0;
	timer=0;
	finder=0;
	//attack_damage=10;
	set_attack_cycle(300);
	set_max_hp(ball->get_hp());

	Weapon* weapon=WeaponCreator::get_cur_object()->create("MissileLauncher");
	weapon->set_attack_range(8.0);
	weapon->set_attack_damage(10);
	weapon->set_attack_size(0.36);

	push_weapon(weapon);
}
void Ball::unit_create(){
	weapons.at(0)->set_attack_size(1.5*rigid_body.radius);
	weapons.at(0)->set_pos(math::vec3<double>(0,0.55*(get_size().y),0));
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
	fscanf(file,"%d\n",&flag);
	if(flag){
		if(finder)delete finder;
		AI::search::FindPath* path=new AI::search::FindPath();
		path->load(file);
		finder=new Tim::SmartPointer<AI::search::Finder>(path);
	}
}
void Ball::killed(){
	Player *cur_player=PlayerController::get_cur_object()->get_cur_player();
	//srand(time(NULL));
	cur_player->modify_resource("cube",1*(get_max_hp()/50));
	int ran=rand()%20;
	//std::cout<<"ran="<<ran<<std::endl;

	switch(ran){
		case 0:
			cur_player->modify_resource("cube",1*(get_max_hp()/30));
			break;
		case 1:
			cur_player->modify_resource("water",1*(get_max_hp()/100));
			break;
		case 2:
			cur_player->modify_resource("fire",1*(get_max_hp()/100));
			break;
		case 3:
			cur_player->modify_resource("earth",1*(get_max_hp()/100));
			break;
		case 4:
			cur_player->modify_resource("air",1*(get_max_hp()/100));
			break;
		default:
			cur_player->modify_resource("cube",1*(get_max_hp()/50));
			break;
	}

	Audio::AudioController::get_cur_object()->play("default_sound_effect/Pickup_Coin2.wav",0.3);
	//cur_player->modify_resource("tech",1*(get_max_hp()/100));
}
void Ball::minion_update(){
	//attack_update();
	ball_move();
	timer++;
	rigid_body.mass=rigid_body.radius*rigid_body.radius*rigid_body.radius;
	if(timer>5000)set_hp(0);
}
void Ball::find_path(){
	Unit* target;
	target=UnitController::get_cur_object()->search_unit("MainTower",rigid_body.pos);
	if(target){

		math::vec3<int>des(target->get_mid_pos_int());
		//std::cout<<"get_pos_int():"<<des.x<<","<<des.y<<","<<des.z<<std::endl;
		AI::search::FindPath *find=new AI::search::FindPath(
				rigid_body.pos,2*rigid_body.radius,des,3);
		if(finder)delete finder;

		finder=new Tim::SmartPointer<AI::search::Finder>(find);
		finder->get()->max_search_times=40000;
		finder->get()->min_search_times=2000;
		AI::search::SearchTask *task=new AOC::AI::search::SearchTask(*finder);
		AI::search::Astar::get_cur_object()->push_task(task);
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
			if(rigid_body.collided_id.size()>0){
				colli_timer=10;
			}
			if(colli_timer<=0&&Map::get_cur_object()->get_cube_down(get_pos()-rigid_body.radius)->standable()){
				math::vec3<double> target=path->path.at(path->cur_at);
				move_to(target,0.008);
				stuck_timer++;
			}else{
				colli_timer--;
				rigid_body.vel.y+=gravity;
			}
		}else{
			if(finder)delete finder;
			finder=0;
			Audio::AudioController::get_cur_object()->
					play_by_dis("default_sound_effect/Bomb.wav",rigid_body.pos,500);
		}
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
		rigid_body.vel.y+=gravity;
	}
}
void Ball::draw_minion(){
	math::vec3<double> pos=get_pos();
	dp_pos.set_pos(glm::vec3(pos.x,pos.y,pos.z));
	dp_pos.set_scale(glm::vec3(2.0*rigid_body.radius,2.0*rigid_body.radius,2.0*rigid_body.radius));
	ball_Drawobj->push_temp_drawdata(new Display::DrawDataObj(&dp_pos));
}
} /* namespace AOC */
