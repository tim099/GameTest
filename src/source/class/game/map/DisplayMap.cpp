#include "class/game/map/DisplayMap.h"
#include "class/display/draw/Draw.h"
#include "class/display/camera/Camera.h"
#include "class/game/map/TaskCreateMapModel.h"
#include "class/tim/thread/ThreadPool.h"
#include "class/game/map/Map.h"
#include <iostream>
DisplayMap::DisplayMap(Map *_map) {
	map = _map;
	max_y = map->get_size().y;
	range = 50;
	createMapObjectMutex = new Tim::Mutex();
	cube = new CubeModel(0.5 * Map::CUBE_SIZE);

	//SEG.x=15;
	static const int Max_seg=25;
	static const int size_per_sig=15;
	seg.x=((double)map->get_size().x/size_per_sig)+0.5;
	seg.y=15;
	seg.z=((double)map->get_size().z/size_per_sig)+0.5;
	if(seg.x<1)seg.x=1;
	if(seg.y<1)seg.y=1;
	if(seg.z<1)seg.z=1;
	if(seg.x>Max_seg)seg.x=Max_seg;
	if(seg.y>Max_seg)seg.y=Max_seg;
	if(seg.z>Max_seg)seg.z=Max_seg;
	segsize.x = ceil((double)map->get_size().x / (double)seg.x);
	segsize.y = map->get_size().y;
	segsize.z = ceil((double)map->get_size().z / (double)seg.z);

	//std::cout<<"Segsize="<<segsize.x<<","<<segsize.y<<","<<segsize.z<<std::endl;
	pos = new Position(glm::vec3(0, 0, 0), glm::vec3());
	dmaps=new Tim::Array2D<MapDrawObject*>(seg.x,seg.z);
	MapDrawObject *d_map;
	for (int i = 0; i < seg.x; i++) {
		for (int j = 0; j < seg.z; j++) {
			d_map = new MapDrawObject("cube/cube_textures","cube/cube_normals");
			//dmaps[i][j] = d_map;
			dmaps->get(i,j)= d_map;
		}
	}
}
DisplayMap::~DisplayMap() {
	delete cube;
	delete createMapObjectMutex;
	for (int i = 0; i < seg.x; i++) {
		for (int j = 0; j < seg.z; j++) {
			//delete dmaps[i][j];
			delete dmaps->get(i,j);
		}
	}
	delete dmaps;
	//delete dmaps[i][j];handle by d_obj
}
void DisplayMap::gen_map_obj(Tim::ThreadPool* threadpool) {
	std::vector<TaskCreateMapModel*> tasks;
	TaskCreateMapModel *task;
	for (int i = 0; i < seg.x; i++) {
		for (int j = 0; j < seg.z; j++) {
			task = new TaskCreateMapModel(this, i, j);
			tasks.push_back(task);
			threadpool->push_task(task);
		}
	}
	for (unsigned i = 0; i < tasks.size(); i++) {
		task = tasks.at(i);
		task->wait_for_this();
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
void DisplayMap::max_y_alter(int val, Tim::ThreadPool* threadpool) {
	if (val == 0)
		return;
	if (val < 0) {
		if (max_y + val > 0)
			max_y += val;
		else
			max_y = 0;
	} else {
		if (max_y + val < map->get_size().y)
			max_y += val;
		else
			max_y = map->get_size().y - 1;
	}

	gen_map_obj(threadpool);
}
void DisplayMap::update_map(glm::ivec3 pos) {
	if ((pos.x / segsize.x) >= seg.x || (pos.x / segsize.x) < 0
			|| (pos.z / segsize.z) >= seg.z || (pos.z / segsize.z) < 0) {
		std::cerr << "DisplayMap::update_map out of range" << std::endl;
		return;
	}
	create_map_object(pos.x / segsize.x, pos.z / segsize.z); //update
	if (pos.x % segsize.x == segsize.x - 1 && ((pos.x / segsize.x) + 1 < seg.x))
		create_map_object((pos.x / segsize.x) + 1, pos.z / segsize.z); //update
	if (pos.x % segsize.x == 0 && ((pos.x / segsize.x) - 1 >= 0))
		create_map_object((pos.x / segsize.x) - 1, pos.z / segsize.z); //update
	if (pos.z % segsize.z == segsize.z - 1 && ((pos.z / segsize.z) + 1 < seg.z))
		create_map_object(pos.x / segsize.x, (pos.z / segsize.z) + 1); //update
	if (pos.z % segsize.z == 0 && ((pos.z / segsize.z) - 1 >= 0))
		create_map_object(pos.x / segsize.x, (pos.z / segsize.z) - 1); //update
}
void DisplayMap::create_map_object(int px, int pz) {
	//Model *mapmodel = dmaps[px][pz]->mapmodel;
	Model *mapmodel =dmaps->get(px,pz)->mapmodel;
	mapmodel->clear();
	int sx=px * segsize.x;
	int ex=(px + 1) * segsize.x;
	if(ex>map->get_size().x)ex=map->get_size().x;
	int sz=pz * segsize.z;
	int ez=(pz + 1) * segsize.z;
	if(ez>map->get_size().z)ez=map->get_size().z;
	for (int i = sx; i < ex; i++) {
		for (int j = 0; j < max_y; j++) {
			for (int k = sz; k < ez; k++) {
				int type = map->get_cube_type(i, j, k);
				if (type) {
					type--; //convert to layer of texture
					glm::vec3 pos = glm::vec3((i + 0.5) * Map::CUBE_SIZE,
							(j + 0.5) * Map::CUBE_SIZE,
							(k + 0.5) * Map::CUBE_SIZE);
					if (j + 1 >= max_y || (map->get_cube_type(i, j + 1, k)<=0)){
						mapmodel->merge(cube->cube[0], pos, type); //DOC->m_objs.at(0)
					}

					if (j - 1 < 0 || map->get_cube_type(i, j - 1, k)<=0){
						mapmodel->merge(cube->cube[1], pos, type);
					}


					if (i + 1 >= map->get_size().x || map->get_cube_type(i + 1, j, k)<=0){
						mapmodel->merge(cube->cube[2], pos, type);
					}

					if (i - 1 < 0 || map->get_cube_type(i - 1, j, k)<=0 ){
						mapmodel->merge(cube->cube[3], pos, type);
					}


					if (k + 1 >= map->get_size().z || map->get_cube_type(i, j, k + 1)<=0){
						mapmodel->merge(cube->cube[4], pos, type);
					}

					if (k - 1 < 0 || map->get_cube_type(i, j, k - 1)<=0 ){
						mapmodel->merge(cube->cube[5], pos, type);
					}

				}
			}
		}
	}
	//dmaps[px][pz]->update_model();
	dmaps->get(px,pz)->update_model();
}
void DisplayMap::draw_map(Camera *camera) {
	glm::ivec2 min, max, dp_pos(camera->look_at.x, camera->look_at.z);

	if (dp_pos.x < 0)
		dp_pos.x = 0;
	if (dp_pos.y < 0)
		dp_pos.y = 0;
	if (dp_pos.x >= map->get_size().x)
		dp_pos.x = map->get_size().x - 1;
	if (dp_pos.y >= map->get_size().z)
		dp_pos.y = map->get_size().z - 1;
	min = dp_pos - glm::ivec2(range, range);
	max = dp_pos + glm::ivec2(range, range);

	glm::ivec2 s=glm::ivec2(((double)min.x / segsize.x),((double)min.y / segsize.z));
	glm::ivec2 e=glm::ivec2(((double)max.x / segsize.x)+1,((double)max.y / segsize.z)+1);
	if(s.x<0)s.x=0;
	if(s.y<0)s.y=0;
	if(e.x>seg.x)e.x=seg.x;
	if(e.y>seg.z)e.y=seg.z;
	//std::cout<<"range="<<range<<std::endl;
	for (int i = s.x; i<e.x; i++) {
		for (int j = s.y; j<e.y; j++) {
			//dmaps[i][j]->push_temp_drawdata(new DrawDataObj(pos,true));//
			dmaps->get(i,j)->push_temp_drawdata(new DrawDataObj(pos,true));
		}
	}
	//std::cout<<"DisplayMap::draw_map end"<<std::endl;
}
