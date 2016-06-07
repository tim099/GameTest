#include "class/game/ageOfCube/map/DisplayMap.h"
#include "class/game/ageOfCube/map/cube/Cube.h"
#include "class/display/draw/Draw.h"
#include "class/display/camera/Camera.h"
#include "class/game/ageOfCube/map/TaskCreateMapModel.h"
#include "class/game/ageOfCube/map/TaskCreateWaterModel.h"
#include "class/game/ageOfCube/map/cube/water/Water.h"
#include "class/tim/thread/ThreadPool.h"
#include "class/game/ageOfCube/map/Map.h"
#include "class/game/ageOfCube/map/MapSeg.h"
#include "class/display/model/modelBuffer/AllModelBuffers.h"
#include <iostream>
namespace AOC{
DisplayMap::DisplayMap(AOC::Map *_map) {
	map = _map;
	display_height = map->get_size().y;
	display_range = 3;
	createMapObjectMutex = new Tim::Mutex();
	cube = new Display::CubeModel(0.5 * Map::CUBE_SIZE);
	gen_display_map_seg();

	pos = new math::Position(glm::vec3(0, 0, 0), glm::vec3());

	dmaps=new Tim::Array2D<MapDrawObject*>(seg.x,seg.z);
	water_dmaps=new Tim::Array2D<WaterDrawObject*>(seg.x,seg.z);

	Display::Draw* cur_draw=Display::Draw::get_cur_object();

	MapDrawObject *d_map;
	WaterDrawObject* d_water;
	for (int i = 0; i < seg.x; i++) {
		for (int j = 0; j < seg.z; j++) {
			d_map = new MapDrawObject("cube/cube_textures","cube/cube_normals");
			dmaps->get(i,j)=d_map;
			cur_draw->push(d_map);

			d_water = new WaterDrawObject();
			water_dmaps->get(i,j)=d_water;
			cur_draw->push(d_water);
		}
	}
}
DisplayMap::~DisplayMap() {
	delete cube;
	delete createMapObjectMutex;
	Display::Draw* cur_draw=Display::Draw::get_cur_object();

	for (int i = 0; i < seg.x; i++) {
		for (int j = 0; j < seg.z; j++) {
			cur_draw->remove(dmaps->get(i,j));
			delete dmaps->get(i,j);

			cur_draw->remove(water_dmaps->get(i,j));
			delete water_dmaps->get(i,j);
		}
	}
	delete dmaps;
	delete water_dmaps;
}
void DisplayMap::gen_display_map_seg(){
	seg=map->seg_num;
	segsize=map->segsize;
	std::cout<<"map_size="<<map->get_size().x<<","<<map->get_size().y<<","
			<<map->get_size().z<<std::endl;
	std::cout<<"Seg="<<seg.x<<","<<seg.y<<","<<seg.z<<std::endl;
	std::cout<<"Segsize="<<segsize.x<<","<<segsize.y<<","<<segsize.z<<std::endl;
}
void DisplayMap::gen_map_model(Tim::ThreadPool* threadpool,
		std::vector<glm::ivec2> &update_maps){
	std::vector<TaskCreateMapModel*> tasks;
	TaskCreateMapModel *task;
	for (unsigned i = 0; i < update_maps.size(); i++) {
			task = new TaskCreateMapModel(this,update_maps[i].x,update_maps[i].y);
			tasks.push_back(task);
			threadpool->push_task(task);
	}
	for (unsigned i = 0; i < tasks.size(); i++) {
		task = tasks.at(i);
		task->join();
		delete task;
	}
}
void DisplayMap::gen_water_model(Tim::ThreadPool* threadpool
		,std::vector<glm::ivec2> &update_waters){
	std::vector<TaskCreateWaterModel*> tasks;
	TaskCreateWaterModel *task;

	for (unsigned i = 0; i < update_waters.size(); i++) {
			task = new TaskCreateWaterModel(this,update_waters[i].x,update_waters[i].y);
			tasks.push_back(task);
			threadpool->push_task(task);
	}
	for (unsigned i = 0; i < tasks.size(); i++) {
		task = tasks.at(i);
		task->join();
		delete task;
	}
}
void DisplayMap::gen_map_obj(){
	for (int i = 0; i < seg.x; i++) {
		for (int j = 0; j < seg.z; j++) {
			create_map_object(i,j);
		}
	}
}
void DisplayMap::update_whole_map(){
	for (int i = 0; i < seg.x; i++) {
		for (int j = 0; j < seg.z; j++) {
			map->get_map_seg(i,j)->updated=true;
			//dmaps->get(i,j)->updated=true;
			//water_dmaps->get(i,j)->updated=true;
		}
	}
}
void DisplayMap::display_height_alter(int val, Tim::ThreadPool* threadpool) {
	if (val == 0)
		return;
	if (val < 0) {
		if (display_height + val > 0)
			display_height += val;
		else
			display_height = 0;
	} else {
		if (display_height + val <=map->get_size().y)
			display_height += val;
		else
			display_height = map->get_size().y;
	}
	update_whole_map();
}
void DisplayMap::update_map(math::vec3<int> pos) {
	if ((pos.x / segsize.x) >= seg.x || (pos.x / segsize.x) < 0
			|| (pos.z / segsize.z) >= seg.z || (pos.z / segsize.z) < 0) {
		std::cerr << "DisplayMap::update_map out of range" << std::endl;
		return;
	}
	map->get_map_seg(pos.x / segsize.x, pos.z / segsize.z)->updated=true;

	if (pos.x % segsize.x == segsize.x - 1 && ((pos.x / segsize.x) + 1 < seg.x)){
		map->get_map_seg((pos.x / segsize.x) + 1, pos.z / segsize.z)->updated=true;
	}
	if (pos.x % segsize.x == 0 && ((pos.x / segsize.x) - 1 >= 0)){
		map->get_map_seg((pos.x / segsize.x) - 1, pos.z / segsize.z)->updated=true;
	}
	if (pos.z % segsize.z == segsize.z - 1 && ((pos.z / segsize.z) + 1 < seg.z)){
		map->get_map_seg(pos.x / segsize.x, (pos.z / segsize.z) + 1)->updated=true;
	}
	if (pos.z % segsize.z == 0 && ((pos.z / segsize.z) - 1 >= 0)){
		map->get_map_seg(pos.x / segsize.x, (pos.z / segsize.z) - 1)->updated=true;
	}

}
void DisplayMap::create_map_object(int px, int pz) {
	//Model *mapmodel = dmaps[px][pz]->mapmodel;
	static const unsigned char up=1<<0;
	static const unsigned char down=1<<1;
	static const unsigned char left=1<<2;
	static const unsigned char right=1<<3;
	static const unsigned char front=1<<4;
	static const unsigned char back=1<<5;
	MapDrawObject *map_dobj=dmaps->get(px,pz);
	Display::Model *mapmodel=map_dobj->model;
	mapmodel->clear();
	int sx=px * segsize.x;
	int ex=(px + 1) * segsize.x;
	if(ex>map->get_size().x)ex=map->get_size().x;
	int sz=pz * segsize.z;
	int ez=(pz + 1) * segsize.z;
	unsigned char cube_exist=0;
	int tex_layer;
	if(ez>map->get_size().z)ez=map->get_size().z;
	for (int i = sx; i < ex; i++) {
		for (int j = 0; j < display_height; j++) {
			for (int k = sz; k < ez; k++) {
				int type = map->get_cube_type(i, j, k);

				if (type>=Cube::cube_start) {
					tex_layer=type-Cube::cube_start;
					cube_exist=0;
					glm::vec3 pos = glm::vec3((i + 0.5) * Map::CUBE_SIZE,
							(j + 0.5) * Map::CUBE_SIZE,
							(k + 0.5) * Map::CUBE_SIZE);

					if((map->get_cube_type(i,j+1,k)>=Cube::cube_start))cube_exist|=up;
					if((map->get_cube_type(i,j-1,k)>=Cube::cube_start))cube_exist|=down;
					if((map->get_cube_type(i+1,j,k)>=Cube::cube_start))cube_exist|=left;
					if((map->get_cube_type(i-1,j,k)>=Cube::cube_start))cube_exist|=right;
					if((map->get_cube_type(i,j,k+1)>=Cube::cube_start))cube_exist|=front;
					if((map->get_cube_type(i,j,k-1)>=Cube::cube_start))cube_exist|=back;

					//if((cube_exist&up)&&(cube_exist&left)&&(cube_exist&right)
							//&&(cube_exist&front)&&(cube_exist&back)){
						//type=0;
					//}
					if (j + 1 >= display_height || !(cube_exist&up)){
						mapmodel->merge(cube->cube[0], pos, tex_layer);
					}

					if (j - 1 < 0 || !(cube_exist&down)){
						mapmodel->merge(cube->cube[1], pos, tex_layer);
					}


					if (i + 1 >= map->get_size().x ||!(cube_exist&left)){
						mapmodel->merge(cube->cube[2], pos, tex_layer);
					}

					if (i - 1 < 0 ||!(cube_exist&right)){
						mapmodel->merge(cube->cube[3], pos, tex_layer);
					}


					if (k + 1 >= map->get_size().z || !(cube_exist&front)){
						mapmodel->merge(cube->cube[4], pos, tex_layer);
					}

					if (k - 1 < 0 || !(cube_exist&back)){
						mapmodel->merge(cube->cube[5], pos, tex_layer);
					}
				}
			}
		}
	}
	map_dobj->update_model();
	map->get_map_seg(px,pz)->updated=false;
}
void DisplayMap::create_water_object(int px, int pz) {
	//Model *watermodel = dmaps[px][pz]->watermodel;

	static const unsigned char up=1<<0;
	static const unsigned char down=1<<1;
	static const unsigned char left=1<<2;
	static const unsigned char right=1<<3;
	static const unsigned char front=1<<4;
	static const unsigned char back=1<<5;
	WaterDrawObject *water_dobj=water_dmaps->get(px,pz);
	Display::Model *watermodel=water_dobj->model;
	watermodel->clear();

	int sx=px * segsize.x;
	int ex=(px + 1) * segsize.x;
	if(ex>map->get_size().x)ex=map->get_size().x;
	int sz=pz * segsize.z;
	int ez=(pz + 1) * segsize.z;
	unsigned char cube_exist=0;

	if(ez>map->get_size().z)ez=map->get_size().z;
	for (int i = sx; i < ex; i++) {
		for (int j = 0; j < display_height; j++) {
			for (int k = sz; k < ez; k++) {
				int type = map->get_cube_type(i, j, k);
				if(Water::is_water(type)){
					cube_exist=0;
					bool surface=false;

					if(map->get_cube_type(i,j+1,k)!=Cube::water){
						surface=true;
					}
					if(map->get_cube_type(i,j+1,k)==Cube::water)cube_exist|=up;
					if((map->get_cube_type(i,j-1,k)>=Cube::cube_start)
							||map->get_cube_type(i,j-1,k)==Cube::water)cube_exist|=down;
					if((map->get_cube_type(i+1,j,k)>=Cube::cube_start)
							||map->get_cube_type(i+1,j,k)==Cube::water)cube_exist|=left;
					if((map->get_cube_type(i-1,j,k)>=Cube::cube_start)
							||map->get_cube_type(i-1,j,k)==Cube::water)cube_exist|=right;
					if((map->get_cube_type(i,j,k+1)>=Cube::cube_start)
							||map->get_cube_type(i,j,k+1)==Cube::water)cube_exist|=front;
					if((map->get_cube_type(i,j,k-1)>=Cube::cube_start)
							||map->get_cube_type(i,j,k-1)==Cube::water)cube_exist|=back;

					//if((cube_exist&up)&&(cube_exist&left)&&(cube_exist&right)
							//&&(cube_exist&front)&&(cube_exist&back)){
						//type=0;
					//}
					glm::vec3 pos = glm::vec3((i + 0.5) * Map::CUBE_SIZE,
							(j + 0.5) * Map::CUBE_SIZE,
							(k + 0.5) * Map::CUBE_SIZE);
					if(surface)pos.y=(j + 0.5) * Map::CUBE_SIZE;
					if (j + 1 >= display_height || !(cube_exist&up)){
						if(surface)watermodel->merge(cube->cube[0], pos);
						else watermodel->merge(cube->cube[0], pos);
					}

					if (j - 1 < 0 || !(cube_exist&down)){
						if(surface)watermodel->merge(cube->cube[1], pos);
						else watermodel->merge(cube->cube[1], pos);
					}


					if (i + 1 >= map->get_size().x ||!(cube_exist&left)){
						if(surface)watermodel->merge(cube->cube[2], pos);
						else watermodel->merge(cube->cube[2], pos);
					}

					if (i - 1 < 0 ||!(cube_exist&right)){
						if(surface)watermodel->merge(cube->cube[3], pos);
						else watermodel->merge(cube->cube[3], pos);
					}
					if (k + 1 >= map->get_size().z || !(cube_exist&front)){
						if(surface)watermodel->merge(cube->cube[4], pos);
						else watermodel->merge(cube->cube[4], pos);
					}

					if (k - 1 < 0 || !(cube_exist&back)){
						if(surface)watermodel->merge(cube->cube[5], pos);
						else watermodel->merge(cube->cube[5], pos);
					}
				}
			}
		}
	}
	//glm::vec3 pos = glm::vec3((sx + 0.5) * Map::CUBE_SIZE,
			//(17) * Map::CUBE_SIZE,
			//(sz + 0.5) * Map::CUBE_SIZE);
	//static Model *waterball=Model::load_obj("files/obj/celestialSphere.obj",50,true);
	//watermodel->merge(waterball,pos);

	water_dobj->update_model();
	//water_dobj->updated=false;
}
math::vec2<int> DisplayMap::get_seg_pos(Display::Camera *camera){
	math::vec2<int> dp_pos(camera->look_at.x/Map::CUBE_SIZE, camera->look_at.z/Map::CUBE_SIZE);

	if (dp_pos.x < 0)dp_pos.x = 0;
	if (dp_pos.y < 0)dp_pos.y = 0;
	if (dp_pos.x >= map->get_size().x)dp_pos.x = map->get_size().x - 1;
	if (dp_pos.y >= map->get_size().z)dp_pos.y = map->get_size().z - 1;
	return math::vec2<int>((dp_pos.x/segsize.x),(dp_pos.y/segsize.z));
}
void DisplayMap::get_draw_range(Display::Camera *camera,math::vec2<int> &start,math::vec2<int> &end){
	math::vec2<int> seg_pos=get_seg_pos(camera);
	start=seg_pos-math::vec2<int>(display_range,display_range);

	if(start.x<0)start.x=0;
	if(start.y<0)start.y=0;

	end=start+math::vec2<int>(2*display_range+1,2*display_range+1);
	if(end.x>seg.x)end.x=seg.x;
	if(end.y>seg.z)end.y=seg.z;
}
void DisplayMap::get_draw_range(Display::Camera *camera,math::vec3<double> &dp_start,
		math::vec3<double> &dp_end){
	dp_start.x=dp_s.x*segsize.x*Map::CUBE_SIZE;
	dp_start.y=0;
	dp_start.z=dp_s.y*segsize.z*Map::CUBE_SIZE;

	dp_end.x=dp_e.x*segsize.x*Map::CUBE_SIZE;
	dp_end.y=(display_height+1)*Map::CUBE_SIZE;
	dp_end.z=dp_e.y*segsize.z*Map::CUBE_SIZE;
}
void DisplayMap::draw_map(Display::Camera *camera,Tim::ThreadPool* threadpool) {
	//std::cout<<"range="<<range<<std::endl;
	get_draw_range(camera,dp_s,dp_e);
	get_draw_range(camera,dp_start,dp_end);
	std::vector<glm::ivec2> update_maps;//test
	std::vector<glm::ivec2> update_waters;//test
	MapDrawObject* dmap;
	WaterDrawObject* dwater;
	for (int i = dp_s.x; i<dp_e.x; i++) {
		for (int j = dp_s.y; j<dp_e.y; j++) {
			dmap=dmaps->get(i,j);
			dwater=water_dmaps->get(i,j);
			//std::cout<<"drawmap at="<<i<<","<<j<<std::endl;
			if(map->get_map_seg(i,j)->updated){
				update_maps.push_back(glm::ivec2(i,j));
				update_waters.push_back(glm::ivec2(i,j));
			}
			dwater->draw=true;
			dwater->push_temp_drawdata(new Display::DrawDataObj(pos,true));

			dmap->draw=true;
			dmap->push_temp_drawdata(new Display::DrawDataObj(pos,true));

			//draw CubeEX
			map->get_map_seg(i,j)->draw(display_height);
		}
	}
	char dphbuff[20];
	sprintf(dphbuff, "display_height=%d\n", display_height);
	Display::Draw::get_cur_object()->push(new Display::RenderString(dphbuff,
			0.015, glm::vec2(0.8, 1.0)));
	gen_map_model(threadpool,update_maps);
	gen_water_model(threadpool,update_waters);
	Display::Draw::get_cur_object()->water_height=map->get_water_height()*Map::CUBE_SIZE;
	//std::cout<<"DisplayMap::draw_map end"<<std::endl;
}
}
