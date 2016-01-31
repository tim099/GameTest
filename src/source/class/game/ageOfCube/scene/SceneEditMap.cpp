#include "class/game/ageOfCube/scene/SceneEditMap.h"
#include "class/display/UI/page/PageControl.h"
#include <ctime>
SceneEditMap::SceneEditMap(std::string _map_name, glm::ivec3 _map_size) {
	map_name = _map_name;
	map_size = _map_size;
	map = 0;
	dmap = 0;
	camera = 0;
	lightControl = 0;
	UI = 0;
}
void SceneEditMap::scene_initialize() {
	map = new Map();
	//map->gen_map(map_size,time(NULL));
	map->load_map("files/maps/map011");
	dmap = new DisplayMap(map);
	dmap->gen_map_obj(thread_pool);
	camera = new Camera(glm::vec3(36.0, 24.0, 24.0),
			glm::vec3(34.0, 22.0, 27.0), glm::vec3(0, 1, 0), 60.0, 0.1f,
			10000.0f);
	lightControl = new LightControl(120);
	lightControl->push_light(
			new ParallelLight(glm::vec3(1.0, -1.2, 0.2),
					glm::vec3(1.9, 1.9, 1.9), true));
	draw->Enable3D = true;
	draw->set_camera(camera);
	draw->set_lightControl(lightControl);
	resume();
	//========================
	std::cout << "SceneEditMap::scene_initialize()" << std::endl;
}
void SceneEditMap::scene_terminate() {
	delete lightControl;
	delete camera;
	delete dmap;
	delete map;
	if (UI) {
		delete UI;
		UI = 0;
	}
}
SceneEditMap::~SceneEditMap() {

}
void SceneEditMap::handle_input() {
	if (input->mouse->mid_pressed()) {
		//std::cout<<"move"<<(int)(mouse->pos.x)<<","<<(int)mouse->prev_pos.x<<std::endl;
		camera->rotate(glm::vec3(0, 1, 0), -0.15 * input->mouse->pos_delta().x);
		camera->rotate(camera->yaw_vec(), 0.15 * input->mouse->pos_delta().y);
	}
	if (input->mouse->right_pressed()) {
		camera->v += (float) (0.001f * sqrt(camera->look_dis() + 0.001)
				* input->mouse->pos_delta().y) * camera->look_vec_xz();
		camera->v += (float) (-0.001f * sqrt(camera->look_dis() + 0.001)
				* input->mouse->pos_delta().x)
				* glm::cross(camera->look_vec_xz(), glm::vec3(0, 1, 0));
	}
	if (input->mouse->left_pressed()) {
		camera->v += (float) (-0.0005f * sqrt(camera->look_dis() + 0.001)
				* input->mouse->pos_delta().y) * glm::vec3(0, 1, 0);
		camera->v += (float) (-0.001f * sqrt(camera->look_dis() + 0.001)
				* input->mouse->pos_delta().x)
				* glm::cross(camera->look_vec_xz(), glm::vec3(0, 1, 0));
	}
	if (input->mouse->scroll) {
		std::cout<<"scroll:"<<sqrt(camera->look_dis() + 0.1)
						* (0.05 * input->mouse->scroll)<<std::endl;
		camera->dis_alter_v += sqrt(camera->look_dis() + 0.1)
				* (0.05 * input->mouse->scroll);
	}
	if (input->keyboard->pressed_char('w')) {
		dmap->max_y_alter(1, thread_pool);
	}
	if (input->keyboard->pressed_char('s')) {
		dmap->max_y_alter(-1, thread_pool);
	}
}
void SceneEditMap::scene_update() {
	//std::cout<<"scene_update()"<<std::endl;
	//UI->update_UIObject();
	camera->update();
	handle_input();
}
void SceneEditMap::scene_draw() {
	dmap->draw_map(camera); //push position
	//UI->draw_UIObject(draw);
}
void SceneEditMap::pause() {
	if (UI) {
		delete UI;
		UI = 0;
	}
}
void SceneEditMap::resume() {
	//draw->Enable3D=false;
	UI = new UI::UI("files/AgeOfCube/startScene/UI/startSceneUI.txt");
	UI::PageControl* p_control = (UI::PageControl*) UI->get_child(
			"pageControl");
	if (!p_control) {
		std::cerr
				<< "SceneStart::scene_initialize ,can't find child page control"
				<< std::endl;
	} else {
		p_control->switch_page("startPage");
	}
}
