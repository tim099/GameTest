#include "class/game/ageOfCube/scene/SceneEditMap.h"
#include "class/display/UI/page/PageControl.h"

#include <ctime>
namespace AOC{
SceneEditMap::SceneEditMap(std::string _map_name, glm::ivec3 _map_size) {
	map_name = _map_name;
	map_size = _map_size;
	map = 0;
	camera = 0;
	lightControl = 0;
	UI = 0;
	destruct_mode=false;
	cl=0;
}
void SceneEditMap::scene_initialize() {
	map = new Map();
	map->gen_map(map_size,time(NULL));

	glm::vec3 pos(0,50,0);
	camera = new Camera(pos,
			pos+glm::vec3(1,-10,1), glm::vec3(0, 1, 0), 60.0, 0.1f,
			10000.0f);
	lightControl = new LightControl(120);
	lightControl->push_light(
			new ParallelLight(glm::vec3(1.0, -1.2, 0.2),
					glm::vec3(1.9, 1.9, 1.9), true));
	draw->Enable3D = true;
	draw->set_camera(camera);
	draw->set_lightControl(lightControl);
	UI = new UI::UI("files/AgeOfCube/editMap/UI/editMapUI.txt");
	cl=new CubeLight();
	cl->color=glm::vec3(1,0.5,0);
	cl->size=1.01f*Map::CUBE_SIZE;
	lightControl->push_light(cl);
	resume();
	//========================
	std::cout << "SceneEditMap::scene_initialize()" << std::endl;
}
void SceneEditMap::scene_terminate() {
	delete lightControl;
	delete camera;

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
	if (input->mouse->left_clicked()) {//->left_pressed()
		if(!destruct_mode){
			map->set_cube_type(map->selected_on.x,
							   map->selected_on.y,
							   map->selected_on.z,
							   Cube::dirt);
		}else{
			map->set_cube_type(map->selected_cube.x,
							   map->selected_cube.y,
							   map->selected_cube.z,
							   Cube::cubeNull);
		}

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
void SceneEditMap::handle_input() {
	camera_control();
	if (input->keyboard->pressed_char('w')) {
		map->dp_map->display_height_alter(1, thread_pool);
	}
	if (input->keyboard->pressed_char('s')) {
		map->dp_map->display_height_alter(-1, thread_pool);
	}
	if (input->keyboard->get('I')) {
		map->dp_map->range += 1;
	}
	if (input->keyboard->get('K')) {
		if (map->dp_map->range > 1)
			map->dp_map->range -= 1;
		else
			map->dp_map->range = 0;
	}
	if (input->keyboard->pressed('B')) {
		glm::ivec3 pos = Map::convert_position(camera->look_at);
		if (!map->get_cube_type(pos.x, pos.y, pos.z)) {
			if (map->set_cube_type(pos.x, pos.y, pos.z, Cube::stone)) {
				//dmap->update_map(pos);
			}
		}
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
	timer.tic(1);
	camera->update();
	handle_input();
	map->update(&timer);


}
void SceneEditMap::scene_draw() {
	UI->draw_UIObject(draw);
	map->dp_map->draw_map(camera,thread_pool); //push position
	if(destruct_mode){
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
void SceneEditMap::pause() {
	if (UI) {
		delete UI;
		UI = 0;
	}
}
void SceneEditMap::resume() {
	//draw->Enable3D=false;

}
}
