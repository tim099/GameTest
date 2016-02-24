#include "class/game/map/cube/Cube.h"
#include "class/game/map/DisplayMap.h"
#include "class/display/draw/Draw.h"
#include "class/display/camera/Camera.h"
#include "class/game/map/TaskCreateMapModel.h"
#include "class/tim/thread/ThreadPool.h"
#include "class/game/map/Map.h"
#include "class/game/map/MapSeg.h"

#include <iostream>
DisplayMap::DisplayMap(Map *_map) {
	map = _map;
	display_height = map->get_size().y;
	range = 3;
	createMapObjectMutex = new Tim::Mutex();
	cube = new CubeModel(0.5 * Map::CUBE_SIZE);
	water_cube = new CubeModel(0.5*Map::CUBE_SIZE,0.45*Map::CUBE_SIZE,0.5*Map::CUBE_SIZE);
	gen_display_map_seg();

	pos = new Position(glm::vec3(0, 0, 0), glm::vec3());
	dmaps=new Tim::Array2D<MapDrawObject*>(seg.x,seg.z);
	MapDrawObject *d_map;
	for (int i = 0; i < seg.x; i++) {
		for (int j = 0; j < seg.z; j++) {
			d_map = new MapDrawObject("cube/cube_textures","cube/cube_normals");
			dmaps->get(i,j)=d_map;
		}
	}
}
DisplayMap::~DisplayMap() {
	delete cube;
	delete water_cube;
	delete createMapObjectMutex;
	for (int i = 0; i < seg.x; i++) {
		for (int j = 0; j < seg.z; j++) {
			delete dmaps->get(i,j);
		}
	}
	delete dmaps;
}
void DisplayMap::gen_display_map_seg(){
	seg=map->seg;
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
			dmaps->get(i,j)->map_updated=true;
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
		if (display_height + val < map->get_size().y)
			display_height += val;
		else
			display_height = map->get_size().y - 1;
	}
	update_whole_map();
}
void DisplayMap::update_map(glm::ivec3 pos) {
	if ((pos.x / segsize.x) >= seg.x || (pos.x / segsize.x) < 0
			|| (pos.z / segsize.z) >= seg.z || (pos.z / segsize.z) < 0) {
		std::cerr << "DisplayMap::update_map out of range" << std::endl;
		return;
	}
	dmaps->get(pos.x / segsize.x, pos.z / segsize.z)->map_updated=true;

	if (pos.x % segsize.x == segsize.x - 1 && ((pos.x / segsize.x) + 1 < seg.x)){
		dmaps->get((pos.x / segsize.x) + 1, pos.z / segsize.z)->map_updated=true;
	}
	if (pos.x % segsize.x == 0 && ((pos.x / segsize.x) - 1 >= 0)){
		dmaps->get((pos.x / segsize.x) - 1, pos.z / segsize.z)->map_updated=true;
	}
	if (pos.z % segsize.z == segsize.z - 1 && ((pos.z / segsize.z) + 1 < seg.z)){
		dmaps->get(pos.x / segsize.x, (pos.z / segsize.z) + 1)->map_updated=true;
	}
	if (pos.z % segsize.z == 0 && ((pos.z / segsize.z) - 1 >= 0)){
		dmaps->get(pos.x / segsize.x, (pos.z / segsize.z) - 1)->map_updated=true;
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
	Model *mapmodel=map_dobj->mapmodel;
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

				if (type>=Cube::startcube) {
					tex_layer=type-Cube::startcube;
					cube_exist=0;
					glm::vec3 pos = glm::vec3((i + 0.5) * Map::CUBE_SIZE,
							(j + 0.5) * Map::CUBE_SIZE,
							(k + 0.5) * Map::CUBE_SIZE);

					if((map->get_cube_type(i,j+1,k)>=Cube::startcube))cube_exist|=up;
					if((map->get_cube_type(i,j-1,k)>=Cube::startcube))cube_exist|=down;
					if((map->get_cube_type(i+1,j,k)>=Cube::startcube))cube_exist|=left;
					if((map->get_cube_type(i-1,j,k)>=Cube::startcube))cube_exist|=right;
					if((map->get_cube_type(i,j,k+1)>=Cube::startcube))cube_exist|=front;
					if((map->get_cube_type(i,j,k-1)>=Cube::startcube))cube_exist|=back;

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

				}else if(type>=Cube::water){
					tex_layer=0;
					cube_exist=0;
					bool surface=false;

					if(map->get_cube_type(i,j+1,k)==Cube::cubeNull){
						surface=true;
					}
					if(map->get_cube_type(i,j+1,k)==Cube::water)cube_exist|=up;
					if((map->get_cube_type(i,j-1,k)>=Cube::startcube)
							||map->get_cube_type(i,j-1,k)==Cube::water)cube_exist|=down;
					if((map->get_cube_type(i+1,j,k)>=Cube::startcube)
							||map->get_cube_type(i+1,j,k)==Cube::water)cube_exist|=left;
					if((map->get_cube_type(i-1,j,k)>=Cube::startcube)
							||map->get_cube_type(i-1,j,k)==Cube::water)cube_exist|=right;
					if((map->get_cube_type(i,j,k+1)>=Cube::startcube)
							||map->get_cube_type(i,j,k+1)==Cube::water)cube_exist|=front;
					if((map->get_cube_type(i,j,k-1)>=Cube::startcube)
							||map->get_cube_type(i,j,k-1)==Cube::water)cube_exist|=back;

					//if((cube_exist&up)&&(cube_exist&left)&&(cube_exist&right)
							//&&(cube_exist&front)&&(cube_exist&back)){
						//type=0;
					//}
					glm::vec3 pos = glm::vec3((i + 0.5) * Map::CUBE_SIZE,
							(j + 0.5) * Map::CUBE_SIZE,
							(k + 0.5) * Map::CUBE_SIZE);
					if(surface)pos.y=(j + 0.45) * Map::CUBE_SIZE;
					if (j + 1 >= display_height || !(cube_exist&up)){
						if(surface)mapmodel->merge(water_cube->cube[0], pos, tex_layer);
						else mapmodel->merge(cube->cube[0], pos, tex_layer);
					}

					if (j - 1 < 0 || !(cube_exist&down)){
						if(surface)mapmodel->merge(water_cube->cube[1], pos, tex_layer);
						else mapmodel->merge(cube->cube[1], pos, tex_layer);
					}


					if (i + 1 >= map->get_size().x ||!(cube_exist&left)){
						if(surface)mapmodel->merge(water_cube->cube[2], pos, tex_layer);
						else mapmodel->merge(cube->cube[2], pos, tex_layer);
					}

					if (i - 1 < 0 ||!(cube_exist&right)){
						if(surface)mapmodel->merge(water_cube->cube[3], pos, tex_layer);
						else mapmodel->merge(cube->cube[3], pos, tex_layer);
					}


					if (k + 1 >= map->get_size().z || !(cube_exist&front)){
						if(surface)mapmodel->merge(water_cube->cube[4], pos, tex_layer);
						else mapmodel->merge(cube->cube[4], pos, tex_layer);
					}

					if (k - 1 < 0 || !(cube_exist&back)){
						if(surface)mapmodel->merge(water_cube->cube[5], pos, tex_layer);
						else mapmodel->merge(cube->cube[5], pos, tex_layer);
					}
				}
			}
		}
	}
	map_dobj->update_model();
	map_dobj->map_updated=false;
}
void DisplayMap::draw_map(Camera *camera,Tim::ThreadPool* threadpool) {
	glm::ivec2 dp_pos(camera->look_at.x, camera->look_at.z);

	if (dp_pos.x < 0)dp_pos.x = 0;
	if (dp_pos.y < 0)dp_pos.y = 0;
	if (dp_pos.x >= map->get_size().x)dp_pos.x = map->get_size().x - 1;
	if (dp_pos.y >= map->get_size().z)dp_pos.y = map->get_size().z - 1;

	glm::ivec2 seg_pos=glm::ivec2((dp_pos.x/segsize.x),(dp_pos.y/segsize.z));

	glm::ivec2 s=seg_pos-glm::ivec2(range,range);
	glm::ivec2 e=seg_pos+glm::ivec2(range+1,range+1);

	if(s.x<0)s.x=0;
	if(s.y<0)s.y=0;
	if(e.x>seg.x)e.x=seg.x;
	if(e.y>seg.z)e.y=seg.z;
	//std::cout<<"range="<<range<<std::endl;

	std::vector<glm::ivec2> update_maps;//test
	MapDrawObject* dmap;

	for (int i = s.x; i<e.x; i++) {
		for (int j = s.y; j<e.y; j++) {
			dmap=dmaps->get(i,j);
			//std::cout<<"drawmap at="<<i<<","<<j<<std::endl;
			if(dmap->map_updated){
				update_maps.push_back(glm::ivec2(i,j));
				//dmap->map_updated=false;
			}
			dmap->draw_map=true;
			dmap->push_temp_drawdata(new DrawDataObj(pos,true));
			map->get_map_seg(i,j)->draw(display_height);
		}
	}
	char dphbuff[20];
	sprintf(dphbuff, "display_height=%d\n", display_height);
	Draw::get_cur_object()->push(new RenderString(dphbuff,
			0.015, glm::vec2(0.8, 1.0)));
	gen_map_model(threadpool,update_maps);

	//std::cout<<"DisplayMap::draw_map end"<<std::endl;
}
