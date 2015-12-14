#include "class/game/map/DisplayMap.h"
#include "class/display/draw/Draw.h"
#include "class/display/texture/TextureMap.h"
#include "class/display/camera/Camera.h"
#include "class/game/map/TaskCreateMapModel.h"
#include "class/tim/thread/ThreadPool.h"
#include "class/display/window/Window.h"
#include "class/game/map/Map.h"
#include <iostream>
DisplayMap::DisplayMap(Map *_map,Draw *_d_obj,TextureMap *_texmap,Window *_window) {
	map=_map;
	d_obj=_d_obj;
	texmap=_texmap;
	window=_window;
	max_y=MY;
	range=70;
	createMapObjectMutex=new Tim::Mutex();
	cube=new CubeModel(0.5*CUBE_SIZE);
	segsize=floor(MX/SEG);
	MapDrawObject *d_map;
    for(int i=0;i<SEG;i++){
    	for(int j=0;j<SEG;j++){
    		//d_map=new MapDrawObject(0,texmap->get_tex(std::string("tex3")),//"test3"
    				//texmap->get_tex(std::string("NormalTexture3")));//"NormalTexture"
    		d_map=new MapDrawObject(0,texmap->get_tex(std::string("cube_textures")),//"test3"
    				texmap->get_tex(std::string("cube_normals")));//
    		d_obj->push(d_map);
    		dmaps[i][j]=d_map;
    	}
    }
}
DisplayMap::~DisplayMap() {
	delete cube;
	delete createMapObjectMutex;
    //delete dmaps[i][j];handle by d_obj
}
void DisplayMap::gen_map_obj(Tim::ThreadPool* threadpool){
	std::vector<TaskCreateMapModel*>tasks;
	TaskCreateMapModel *task;
    for(int i=0;i<SEG;i++){
    	for(int j=0;j<SEG;j++){
    		task=new TaskCreateMapModel(this,i,j);
    		tasks.push_back(task);
    		threadpool->push_task(task);
    	}
    }
    while(!tasks.empty()){
    	while(!tasks.front()->Done()){

    	}
    	task=tasks.front();
    	delete task;
    	tasks.front()=tasks.back();
		tasks.pop_back();
    }
}
void DisplayMap::max_y_alter(int val,Tim::ThreadPool* threadpool){
	if(val==0)return;
	if(val<0){
		if(max_y+val>0)max_y+=val;
		else max_y=0;
	}else{
		if(max_y+val<MY)max_y+=val;
		else max_y=MY-1;
	}

	gen_map_obj(threadpool);
}
void DisplayMap::update_map(int x,int y,int z){
	//window->render_on();
	create_map_object(x/segsize,z/segsize);//update
	if(x%segsize==segsize-1&&((x/segsize)+1<SEG))create_map_object((x/segsize)+1,z/segsize);//update
	if(x%segsize==0&&((x/segsize)-1>=0))create_map_object((x/segsize)-1,z/segsize);//update
	if(z%segsize==segsize-1&&((z/segsize)+1<SEG))create_map_object(x/segsize,(z/segsize)+1);//update
	if(z%segsize==0&&((z/segsize)-1>=0))create_map_object(x/segsize,(z/segsize)-1);//update
	//Window::render_off();
}
void DisplayMap::create_map_object(int px,int pz){
	Model *mapmodel=dmaps[px][pz]->mapmodel;

	mapmodel->clear();
    for(int i=px*segsize;i<(px+1)*segsize;i++){
    	for(int j=0;j<max_y;j++){
    		for(int k=pz*segsize;k<(pz+1)*segsize;k++){
    			int type=map->get(i,j,k);
    			if(type){
    				type--;//convert to layer of texture
    				glm::vec3 pos=glm::vec3((i+0.5)*CUBE_SIZE,(j+0.5)*CUBE_SIZE,(k+0.5)*CUBE_SIZE);
        			if(j+1>=max_y||!map->get(i,j+1,k))mapmodel->merge(cube->cube[0],pos,type);//DOC->m_objs.at(0)
        			if(j-1<0||!map->get(i,j-1,k))mapmodel->merge(cube->cube[1],pos,type);
        			if(i+1>=MX||!map->get(i+1,j,k))mapmodel->merge(cube->cube[2],pos,type);
        			if(i-1<0||!map->get(i-1,j,k))mapmodel->merge(cube->cube[3],pos,type);
        			if(k+1>=MZ||!map->get(i,j,k+1))mapmodel->merge(cube->cube[4],pos,type);
        			if(k-1<0||!map->get(i,j,k-1))mapmodel->merge(cube->cube[5],pos,type);
    			}
    		}
    	}
    }
    dmaps[px][pz]->update_model();
}
void DisplayMap::draw_map(Camera *camera){
    glm::ivec2 min,max,dp_pos(camera->look_at.x,camera->look_at.z);
    if(dp_pos.x<0)dp_pos.x=0;if(dp_pos.y<0)dp_pos.y=0;
    if(dp_pos.x>=MX)dp_pos.x=MX-1;if(dp_pos.y>=MZ)dp_pos.y=MZ-1;
    min=dp_pos-glm::ivec2(range,range);
    max=dp_pos+glm::ivec2(range,range);
    if(min.x<0)min.x=0;if(min.y<0)min.y=0;
    if(max.x>=MX)max.x=MX-1;if(max.y>=MZ)max.y=MZ-1;

    for(int i=(min.x/segsize);i<(max.x/segsize+0.5);i++){
    	for(int j=min.y/segsize;j<(max.y/segsize+0.5);j++){
    		dmaps[i][j]->push_temp_position(new Position(glm::vec3(0,0,0),glm::vec3()));
    	}
    }
}
