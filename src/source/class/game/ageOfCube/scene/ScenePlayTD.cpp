#include "class/game/ageOfCube/map/building/BuildingCreator.h"
#include "class/game/ageOfCube/scene/ScenePlayTD.h"
#include "class/display/UI/page/PageControl.h"
#include "class/tim/file/File.h"
#include <ctime>
namespace AOC{
ScenePlayTD::ScenePlayTD(std::string _map_name, glm::ivec3 _map_size) {
	map_name = _map_name;
	map_size = _map_size;
	map = 0;
	camera = 0;
	lightControl = 0;
	UI = 0;
	cl=0;
	constructing_building=0;
	mode = normal;
}
void ScenePlayTD::loading(){
	if(Tim::File::check_if_file_exist(map_name)){
		map->load_map(map_name);
	}else{
		map->gen_map(map_size,time(NULL));
	}

}
void ScenePlayTD::scene_initialize() {
	map = new AOC::Map();

	glm::vec3 pos(10,80,10);
	camera = new Display::Camera(pos,
			pos+glm::vec3(10,-10,10), glm::vec3(0, 1, 0), 60.0, 0.1f,
			10000.0f);
	lightControl = new Display::LightControl(120);
	lightControl->push_light(
			new Display::ParallelLight(glm::vec3(1.0, -1.2, 0.2),
					glm::vec3(1.9, 1.9, 1.9), true));

	UI = new UI::UI();
	UI->Load_script("files/AgeOfCube/scenes/playTD/UI/playTD_UI.txt");
	//UI->Load_script("files/script/UIscript/saveUI.txt");


	cl=new Display::CubeLight();
	cl->color=glm::vec3(1,0.5,0);
	cl->size=1.01f*Map::CUBE_SIZE;
	lightControl->push_light(cl);
	resume();
	//========================
	//std::cout << "SceneEditMap::scene_initialize()" << std::endl;
}
void ScenePlayTD::scene_terminate() {
	delete lightControl;
	delete camera;
	if(map)delete map;
	if (UI) {
		delete UI;
		UI = 0;
	}
}
ScenePlayTD::~ScenePlayTD() {

}
void ScenePlayTD::camera_control(){

	if(input->keyboard->pressed('R')){
		camera->v.y += 0.01f* sqrt(camera->look_dis() + 0.001);
	}
	if(input->keyboard->pressed('F')){
		camera->v.y -= 0.01f* sqrt(camera->look_dis() + 0.001);
	}
	if (input->mouse->mid_pressed()||input->keyboard->pressed('Z')) {
		//std::cout<<"move"<<(int)(mouse->pos.x)<<","<<(int)mouse->prev_pos.x<<std::endl;
		camera->rotate(glm::vec3(0, 1, 0), -0.15 * input->mouse->pos_delta().x);
		camera->rotate(camera->yaw_vec(), 0.15 * input->mouse->pos_delta().y);
	}
	//camera->rotate(glm::vec3(0, 1, 0), 1.0f);
	if(input->mouse->screen_pos.y>0.95){
		camera->v += (float) (-0.02f * sqrt(camera->look_dis() + 0.001))
				* camera->look_vec_xz();
	}
	if(input->mouse->screen_pos.y<-0.95){
		camera->v += (float) (0.02f * sqrt(camera->look_dis() + 0.001))
				* camera->look_vec_xz();
	}
	if(input->mouse->screen_pos.x>0.95){
		camera->v += (float) (-0.02f * sqrt(camera->look_dis() + 0.001))
		* glm::cross(camera->look_vec_xz(), glm::vec3(0, 1, 0));
	}
	if(input->mouse->screen_pos.x<-0.95){
		camera->v += (float) (0.02f * sqrt(camera->look_dis() + 0.001))
		* glm::cross(camera->look_vec_xz(), glm::vec3(0, 1, 0));
	}
	if (input->mouse->right_pressed()) {
		camera->v += (float) (0.001f * sqrt(camera->look_dis() + 0.001)
				* input->mouse->pos_delta().y) * camera->look_vec_xz();
		camera->v += (float) (-0.001f * sqrt(camera->look_dis() + 0.001)
				* input->mouse->pos_delta().x)
				* glm::cross(camera->look_vec_xz(), glm::vec3(0, 1, 0));
	}
	if (input->mouse->scroll) {
		camera->dis_alter_v += sqrt(camera->look_dis() + 0.1)
				* (0.05 * input->mouse->scroll);
	}
	if(camera->look_at.x>Map::CUBE_SIZE*map->get_size().x+4.0){
		if(camera->v.x>0.0f){
			camera->v.x*=-0.9f;
		}
	}else if(camera->look_at.x<-4.0){
		if(camera->v.x<0.0f){
			camera->v.x*=-0.9f;
		}
	}
	if(camera->look_at.z>Map::CUBE_SIZE*map->get_size().z+4.0){
		if(camera->v.z>0.0f){
			camera->v.z*=-0.9f;
		}
	}else if(camera->look_at.z<-4.0){
		if(camera->v.z<0.0f){
			camera->v.z*=-0.9f;
		}
	}
}
void ScenePlayTD::handle_signal(Input::Signal *sig){
	if(sig->get_data() == "save_map"){
		map->save_map(map_name);
	}
	else if(sig->get_data() == "build"){
		if(constructing_building)delete constructing_building;
		BuildingCreator* creator2=BuildingCreator::get_cur_object();
		constructing_building = creator2->create("Tower");
		mode = constructing;
	}
	else if(sig->get_data() == "reload"){
		reload_map();
	}

}
void ScenePlayTD::handle_input() {
	camera_control();
	if (input->mouse->left_clicked()) {//->left_pressed()

		Cube *selected_cube =  map->get_cube(map->selected_cube.x,
					   	   	   	   	   	   	   map->selected_cube.y,
											   map->selected_cube.z);


		if(Building *selected_building = dynamic_cast<Building *>(selected_cube) ){
			std::cout<<"building selected. hp="<<selected_building->get_hp()
					<<"/"<<selected_building->get_max_hp()<<std::endl;
			map->unit_controller->select_unit(selected_building);
			return;
		}else{
			map->unit_controller->deselect_unit();
		}

		if(mode == constructing){

			//BuildingCreator* creator2=BuildingCreator::get_cur_object();
			//constructing_building = creator2->create("Tower");
			if(constructing_building->build(map,map->selected_on.x,
					map->selected_on.y,
					map->selected_on.z)){
				constructing_building=0;
			}else{
				delete constructing_building;
				constructing_building=0;
			}

			/*
			map->push_CubeEX(map->selected_on.x,
							   map->selected_on.y,
							   map->selected_on.z,
							   building);
			*/
			mode = normal;
		}else if(mode == removing){
			map->set_cube_type(map->selected_cube.x,
							   map->selected_cube.y,
							   map->selected_cube.z,
							   Cube::cubeNull);
		}else{
			map->set_cube_type(map->selected_on.x,
							   map->selected_on.y,
							   map->selected_on.z,
							   Cube::dirt);
		}

	}
	if (input->keyboard->pressed_char('w')) {
		map->dp_map->display_height_alter(1, thread_pool);
	}
	if (input->keyboard->pressed_char('s')) {
		map->dp_map->display_height_alter(-1, thread_pool);
	}
	if (input->keyboard->get('I')) {
		map->dp_map->display_range += 1;
	}

	if (input->keyboard->get('E')) {
		if(!UI->check_mode(UI::Mode::EDIT)){
			UI->Enable_Mode(UI::Mode::EDIT);
		}else{
			UI->Disable_Mode(UI::Mode::EDIT);
		}
	}
	if(input->keyboard->get('S')){
		UI->Save_script("files/AgeOfCube/playTD/UI/playTD_UI.txt");
	}else if(input->keyboard->get('L')){
			//delete UI;
		UI = new UI::UI("files/AgeOfCube/playTD/UI/playTD_UI.txt");
	}
	if (input->keyboard->get('V')) {
		if(mode == normal){
			mode = removing;
		}
		else if(mode == removing){
			mode = normal;
		}
	}
	if (input->keyboard->get('K')) {
		if (map->dp_map->display_range > 1)
			map->dp_map->display_range -= 1;
		else
			map->dp_map->display_range = 0;
	}
	if (input->keyboard->pressed('B')) {
		glm::ivec3 pos = Map::convert_position(camera->look_at);
		if (!map->get_cube_type(pos.x, pos.y, pos.z)) {
			if (map->set_cube_type(pos.x, pos.y, pos.z, Cube::stone)) {
				//dmap->update_map(pos);
			}
		}
	}
	if(input->keyboard->get('S')){
		UI->Save_script("files/AgeOfCube/editMap/UI/editMapUI.txt");
	}
	if (input->keyboard->pressed('V')) {
		glm::ivec3 pos = Map::convert_position(camera->look_at);
		if (map->get_cube_type(pos.x, pos.y, pos.z)) {
			Cube *cube=map->get_cube(pos.x,pos.y,pos.z);
			std::cout<<"cube name="<<cube->get_name()<<std::endl;
			if (map->set_cube_type(pos.x, pos.y, pos.z, 0)) {
				//dmap->update_map(pos);
			}
		}

	}
	if (input->keyboard->pressed(GLFW_KEY_UP)) {
		if (lightControl->shadow_dis > 0.01)
			lightControl->shadow_dis *= 0.98;
	}
	if (input->keyboard->pressed(GLFW_KEY_DOWN)) {
		if (lightControl->shadow_dis < 30.0)
			lightControl->shadow_dis *= 1.01;
	}
}
void ScenePlayTD::scene_update() {
	//std::cout<<"scene_update()"<<std::endl;
	UI->update_UIObject();
	timer.tic(1);
	camera->update();
	map->update(&timer);


}
void ScenePlayTD::scene_update_end(){
	handle_input();
}
void ScenePlayTD::scene_draw() {
	UI->draw_UIObject(draw);

	map->draw(draw,camera,thread_pool); //push position

	if(constructing_building){
		constructing_building->set_player(1);
		if(input->mouse->pos_delta()==glm::ivec2(0,0)){
			constructing_building->draw_buildable(map);
		}else{
			constructing_building->set_pos(map->selected_on.x,
					map->selected_on.y,
					map->selected_on.z);
		}

	}
	if(mode == removing){
		cl->color=glm::vec3(1,0,0);
		cl->pos=glm::vec3((map->selected_cube.x+0.5f)*Map::CUBE_SIZE,
						  (map->selected_cube.y+0.5f)*Map::CUBE_SIZE,
						  (map->selected_cube.z+0.5f)*Map::CUBE_SIZE);
	}else{
		cl->color=glm::vec3(0,1,0);
		cl->pos=glm::vec3((map->selected_on.x+0.5f)*Map::CUBE_SIZE,
				  (map->selected_on.y+0.5f)*Map::CUBE_SIZE,
				  (map->selected_on.z+0.5f)*Map::CUBE_SIZE);
	}
}
void ScenePlayTD::pause() {

}
void ScenePlayTD::resume() {
	draw->Enable3D = true;
	draw->set_camera(camera);
	draw->set_lightControl(lightControl);
	map->unit_controller->register_cur();
}

void ScenePlayTD::reload_map(){

	Input::Signal *sig=new Input::Signal("push_scene","Game");
	Input::Signal *sig2=new Input::Signal("pop_scene","Game");

	sig2->sent();

	sig->ex_data=new AOC::ScenePlayTD(map_name,glm::ivec3(1,1,1));
	sig->sent();
}

}
