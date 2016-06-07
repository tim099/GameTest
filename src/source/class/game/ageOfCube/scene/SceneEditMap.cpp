#include "class/game/ageOfCube/scene/SceneEditMap.h"
#include "class/display/UI/page/PageControl.h"
#include "class/tim/file/File.h"
#include "class/display/draw/drawObject/AllDrawObjects.h"
#include "class/display/draw/drawObject/drawData/drawDateEX/SkyMap.h"
#include "class/audio/AllAudioSources.h"

#include <ctime>
namespace AOC{
SceneEditMap::SceneEditMap(std::string _map_name, glm::ivec3 _map_size) {
	map_name = _map_name;
	map_size = _map_size;
	map = 0;
	cube_type=0;
	camera = 0;
	lightControl = 0;
	UI = 0;
	back_music=0;
	sun_light=0;
	destruct_mode=false;
	pause_timer=false;
	constructing_building=0;
}
void SceneEditMap::loading(){
	if(Tim::File::check_if_file_exist(map_name)){
		map->load_map(map_name);
	}else{
		map->gen_map(map_size,time(NULL));
	}

}
void SceneEditMap::scene_initialize() {
	map = new AOC::Map();
	glm::vec3 pos(10,80,10);
	sun_col_1=glm::vec3(1.9, 1.9, 1.9);

	camera = new Display::Camera(pos,
			pos+glm::vec3(10,-10,10), glm::vec3(0, 1, 0), 60.0, 0.1f,
			10000.0f);
	lightControl = new Display::LightControl(120);
	sun_pos=glm::vec3(1.0, -1.2, 0.5);
	sun_light=new Display::ParallelLight(sun_pos,sun_col_1, true);

	lightControl->push_light(sun_light);
	lightControl->push_light(
			new Display::ParallelLight(glm::vec3(0.05, -1.2, -0.2),
					glm::vec3(0.3, 0.3, 0.3),false));
	UI = new UI::UI();
	UI->Load_script("files/AgeOfCube/scenes/editMap/UI/editMapUI.txt");
	back_music=new Audio::AudioPlayer();
	back_music->set_source("default_music/prepare_your_swords.wav");
	back_music->set_loop(true);

	cube_type=Cube::cube_start;
	resume();
}
void SceneEditMap::scene_terminate() {
	delete lightControl;
	delete camera;
	if(back_music)delete back_music;
	if(constructing_building)delete constructing_building;
	if(map)delete map;
	if (UI) {
		delete UI;
		UI = 0;
	}
}
SceneEditMap::~SceneEditMap() {

}
void SceneEditMap::camera_control(){
	if(input->keyboard->pressed('R')){
		camera->v.y += 0.01f* sqrt(camera->look_dis() + 0.001);
	}
	if(input->keyboard->pressed('F')){
		camera->v.y -= 0.01f* sqrt(camera->look_dis() + 0.001);
	}
	if(input->keyboard->get('A')&&constructing_building){
		std::cout<<"rotate!!"<<std::endl;
		int cur_rotate=constructing_building->get_rotate();
		if(cur_rotate<3)cur_rotate++;
		else cur_rotate=0;
		constructing_building->set_rotate(cur_rotate);
	}
	if(input->keyboard->get('1')&&constructing_building){
		constructing_building->set_size(1.0);
	}
	if(input->keyboard->get('2')&&constructing_building){
		constructing_building->set_size(2.0);
	}
	if(input->keyboard->get('3')&&constructing_building){
		constructing_building->set_size(3.0);
	}
	if(input->keyboard->get('4')&&constructing_building){
		constructing_building->set_size(4.0);
	}
	if(input->keyboard->get('5')&&constructing_building){
		constructing_building->set_size(5.0);
	}
	if(input->keyboard->get('6')&&constructing_building){
		constructing_building->set_size(6.0);
	}
	if(input->keyboard->get('7')&&constructing_building){
		constructing_building->set_size(7.0);
	}
	if(input->keyboard->get('8')&&constructing_building){
		constructing_building->set_size(8.0);
	}
	if(input->keyboard->get('9')&&constructing_building){
		constructing_building->set_size(9.0);
	}
	if(input->keyboard->get('0')&&constructing_building){
		constructing_building->set_size(10.0);
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
void SceneEditMap::handle_signal(Input::Signal *sig){
	if(sig->get_data()=="save_map"){
		map->save_map(map_name);
	}else if(sig->get_data()=="build_BallSpawnTower"){
		if(constructing_building)delete constructing_building;
		BuildingCreator* creator=BuildingCreator::get_cur_object();
		constructing_building = creator->create("BallSpawnTower");
		constructing_building->set_player(1);//enemy
	}else if(sig->get_data()=="build_Tower"){
		if(constructing_building)delete constructing_building;
		BuildingCreator* creator=BuildingCreator::get_cur_object();
		constructing_building = creator->create("Tower");
		constructing_building->set_player(0);
	}else if(sig->get_data()=="build_MainTower"){
		if(constructing_building)delete constructing_building;
		BuildingCreator* creator=BuildingCreator::get_cur_object();
		constructing_building = creator->create("MainTower");
		constructing_building->set_player(0);
	}
}
void SceneEditMap::handle_input() {
	camera_control();
	if(input->keyboard->get(Input::KeyCode::Plus)){
		//std::cout<<"+ volume"<<std::endl;
		//back_music->set_volume(1.03*back_music->get_volume());
		if(cube_type<Cube::cube_end)cube_type++;
	}
	if(input->keyboard->get(Input::KeyCode::Minus)){
		if(cube_type>Cube::cube_start)cube_type--;
		//std::cout<<"- volume"<<std::endl;
		//back_music->set_volume(0.97*back_music->get_volume());
	}
	if (input->mouse->left_clicked()) {//->left_pressed()
		if(constructing_building){
			if(constructing_building->build()){
			}else{
				delete constructing_building;
			}
			constructing_building=0;
		}else{
			if(!destruct_mode){
				map->set_cube_type(map->selected_on.x,
								   map->selected_on.y,
								   map->selected_on.z,
								   cube_type);
			}else{
				map->set_cube_type(map->selected_cube.x,
								   map->selected_cube.y,
								   map->selected_cube.z,
								   Cube::cubeNull);
			}
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
	/*
	if (input->keyboard->get('E')) {
		if(UI->check_mode(UI::Mode::EDIT)){
			UI->Disable_Mode(UI::Mode::EDIT);
		}else{
			UI->Enable_Mode(UI::Mode::EDIT);
		}
	}
	*/
	if (input->keyboard->get('V')) {
		destruct_mode^=1;
	}
	if(input->keyboard->get('P')){
		pause_timer^=1;
	}
	if (input->keyboard->get('Q')) {
		draw->real_water^=1;
	}
	if(input->keyboard->get('T')){
		timer.tic(1);
		map->update(&timer);
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
void SceneEditMap::scene_update() {



	//std::cout<<"scene_update()"<<std::endl;
	UI->update_UIObject();
	camera->update();
	if(!pause_timer){
		timer.tic(1);
		map->update(&timer);
	}else{
		//std::cout<<"pause"<<std::endl;
	}

}
void SceneEditMap::scene_update_end(){
	handle_input();
}
void SceneEditMap::scene_draw() {
	UI->draw_UIObject(draw);
	map->draw(draw,camera,thread_pool); //push position

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
	sun_light->vec=glm::vec3(galaxy_pos.get_pos_mat()*glm::vec4(glm::vec3(10,-10, 10), 1));
	Display::DrawObject* stars=Display::AllDrawObjects::get_cur_object()->get("default/stars");
	data=new Display::DrawDataObj(&galaxy_pos,false,false);
	stars->push_temp_drawdata(data);
	if(constructing_building){
		if(input->mouse->_pos_delta==glm::ivec2(0,0)){
			constructing_building->draw_buildable(map);
		}else{
			constructing_building->set_pos(
					map->selected_on.x,
					map->selected_on.y,
					map->selected_on.z);
		}

	}else{
		if(destruct_mode){
			Display::CubeLight*cl=new Display::CubeLight();
			cl->size=1.01f*Map::CUBE_SIZE;
			cl->color=glm::vec3(1,0,0);
			cl->pos=glm::vec3((map->selected_cube.x+0.5f)*Map::CUBE_SIZE,
							  (map->selected_cube.y+0.5f)*Map::CUBE_SIZE,
							  (map->selected_cube.z+0.5f)*Map::CUBE_SIZE);
			lightControl->push_temp_light(cl);
		}else{
			Display::CubeLight*cl=new Display::CubeLight();
			cl->size=1.01f*Map::CUBE_SIZE;
			cl->color=glm::vec3(0,1,0);
			cl->pos=glm::vec3((map->selected_on.x+0.5f)*Map::CUBE_SIZE,
					  (map->selected_on.y+0.5f)*Map::CUBE_SIZE,
					  (map->selected_on.z+0.5f)*Map::CUBE_SIZE);
			lightControl->push_temp_light(cl);
		}
	}
}
void SceneEditMap::pause() {
	back_music->pause();
}
void SceneEditMap::resume() {
	back_music->play();
	draw->Enable3D = true;
	draw->set_camera(camera);
	draw->set_lightControl(lightControl);
}
}
