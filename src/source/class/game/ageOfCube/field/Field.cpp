#include "class/game/ageOfCube/field/Field.h"
#include "class/display/draw/drawObject/AllDrawObjects.h"
#include "class/display/draw/drawObject/drawData/drawDateEX/SkyMap.h"
#include "class/game/ageOfCube/map/ai/search/Astar.h"
namespace AOC {

Field::Field() {
	entity_controller=new entity::EntityController();
	unit_controller=new UnitController();
	attack_controller=new AttackController();
	player_controller = new PlayerController();
	map = new Map();
	astar=new AI::search::Astar();
	sun_col_1=glm::vec3(1.9, 1.9, 1.9);
	sun_pos=glm::vec3(1.0, -1.2, 0.5);
	sun_light=new Display::ParallelLight(sun_pos,sun_col_1, true);
	Display::Draw::get_cur_object()->lightControl->push_light(sun_light);
}
Field::~Field() {
	std::cout<<"Field::~Field() 1"<<std::endl;
	delete astar;
	if(map)delete map;
	std::cout<<"Field::~Field() 2"<<std::endl;
	delete player_controller;
	std::cout<<"Field::~Field() 3"<<std::endl;
	delete attack_controller;
	std::cout<<"Field::~Field() 4"<<std::endl;
	delete unit_controller;
	std::cout<<"Field::~Field() 5"<<std::endl;
	delete entity_controller;
	std::cout<<"Field::~Field() 6"<<std::endl;

}
void Field::save(const std::string& path){
	FILE * file = fopen(path.c_str(),"w+t");
	entity_controller->save(file);
	map->save_map(file);
	unit_controller->save(file);
	attack_controller->save(file);

	fclose(file);
}
void Field::load(const std::string& path){
	FILE * file = fopen(path.c_str(),"r");
	entity_controller->load(file);
	map->load_map(file);
	unit_controller->load(file);
	attack_controller->load(file);

	fclose(file);
}
void Field::update(){
	timer.tic(1);
	map->update(&timer);
	unit_controller->update();
	player_controller->update();
	attack_controller->update();
}
void Field::draw(Display::Draw *draw,Display::Camera *camera,Tim::ThreadPool* threadpool){
	map->draw(draw,camera,threadpool);
	unit_controller->draw(draw);
	player_controller->draw(draw);
	attack_controller->draw();
	draw_back_ground();
}
void Field::draw_back_ground(){
	Display::DrawObject* galaxy=Display::AllDrawObjects::get_cur_object()->get("default/galaxy");
	Display::DrawDataObj* data=new Display::DrawDataObj(&galaxy_pos_o,false,false);
	data->push_ex_data(new Display::drawDataEX::SkyMap());
	galaxy->push_temp_drawdata(data);
	galaxy_pos_o.set_r(glm::vec3(60,0,0));
	galaxy_pos.set_parent(&galaxy_pos_o);
	galaxy_pos.set_r(glm::vec3(0.0f,180.0f*timer.get_hour(),0.0f));
	//sun_light->vec=glm::vec3(
			//glm::rotate((float)(360.0f * timer.get_hour()),glm::vec3(-1, 0, 1))
					//*glm::vec4(glm::vec3(10,-10, 10), 1));

	Display::DrawObject* stars=Display::AllDrawObjects::get_cur_object()->get("default/stars");
	data=new Display::DrawDataObj(&galaxy_pos,false,false);
	stars->push_temp_drawdata(data);
	sun_light->vec=glm::vec3(galaxy_pos.get_pos_mat()*glm::vec4(glm::vec3(10,-10, 10), 1));
}
} /* namespace AOC */
