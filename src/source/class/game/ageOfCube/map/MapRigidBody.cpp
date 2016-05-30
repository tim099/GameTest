#include "class/game/ageOfCube/map/MapRigidBody.h"
#include "class/game/ageOfCube/map/Map.h"
#include <set>
#include <queue>
namespace AOC {

MapRigidBody::MapRigidBody(Map *_map) {
	map=_map;
}
MapRigidBody::~MapRigidBody() {

}
void MapRigidBody::collide(RigidBody* b){

}
bool MapRigidBody::handle_stuck(physic::RigidBody* b){
	math::vec3<int> pos((b->pos.x)/Map::CUBE_SIZE,
						(b->pos.y)/Map::CUBE_SIZE,
						(b->pos.z)/Map::CUBE_SIZE);
	if(check_stuck(b)){//stuck

		std::set<math::vec3<int> >visited;
		std::queue<math::vec3<int> >next;
		next.push(pos);visited.insert(pos);
		math::vec3<int> cur;

		bool find=false;

		while(!find&&!next.empty()){
			cur=next.front();
			next.pop();
			b->pos.x=(cur.x+0.5)*Map::CUBE_SIZE;
			b->pos.y=(cur.y+0.5)*Map::CUBE_SIZE;
			b->pos.z=(cur.z+0.5)*Map::CUBE_SIZE;
			if(!check_stuck(b)){
				find=true;
			}else{
				math::vec3<int> tmp;
				tmp=cur;tmp.x+=1;
				if(visited.find(tmp)!=visited.end()){
					next.push(tmp);visited.insert(pos);
				}
				tmp=cur;tmp.x-=1;
				if(visited.find(tmp)!=visited.end()){
					next.push(tmp);visited.insert(pos);
				}
				tmp=cur;tmp.y+=1;
				if(visited.find(tmp)!=visited.end()){
					next.push(tmp);visited.insert(pos);
				}
				tmp=cur;tmp.y-=1;
				if(visited.find(tmp)!=visited.end()){
					next.push(tmp);visited.insert(pos);
				}
				tmp=cur;tmp.z+=1;
				if(visited.find(tmp)!=visited.end()){
					next.push(tmp);visited.insert(pos);
				}
				tmp=cur;tmp.z-=1;
				if(visited.find(tmp)!=visited.end()){
					next.push(tmp);visited.insert(pos);
				}
			}
		}
		return true;
	}
	return false;
}
bool MapRigidBody::MapRigidBody::check_collision(physic::RigidBody* b){
	bool collided=false;
	math::vec3<double> del_pos=b->pos-b->prev_pos;
	math::vec3<int> prev_pos((b->prev_pos.x)/Map::CUBE_SIZE,
			(b->prev_pos.y)/Map::CUBE_SIZE,
			(b->prev_pos.z)/Map::CUBE_SIZE);
	math::vec3<int> pos((b->pos.x)/Map::CUBE_SIZE,
			(b->pos.y)/Map::CUBE_SIZE,
			(b->pos.z)/Map::CUBE_SIZE);
	math::vec3<int> s(
			floor((b->pos.x-1.01*b->radius)/Map::CUBE_SIZE),
			floor((b->pos.y-1.01*b->radius)/Map::CUBE_SIZE),
			floor((b->pos.z-1.01*b->radius)/Map::CUBE_SIZE));
	math::vec3<int> e(
			ceil((b->pos.x+1.01*b->radius)/Map::CUBE_SIZE),
			ceil((b->pos.y+1.01*b->radius)/Map::CUBE_SIZE),
			ceil((b->pos.z+1.01*b->radius)/Map::CUBE_SIZE));

	bool c_x=false,c_y=false,c_z=false;
	float delx,dely,delz;
	for(int i=s.x;i<=e.x;i++){
		for(int j=s.y;j<=e.y;j++){
			for(int k=s.z;k<=e.z;k++){
				if(map->get_cube_type(i,j,k)!=Cube::cubeNull){
					delx=(0.5*Map::CUBE_SIZE+b->radius)-fabs(b->pos.x-(i+0.5)*Map::CUBE_SIZE);
					dely=(0.5*Map::CUBE_SIZE+b->radius)-fabs(b->pos.y-(j+0.5)*Map::CUBE_SIZE);
					delz=(0.5*Map::CUBE_SIZE+b->radius)-fabs(b->pos.z-(k+0.5)*Map::CUBE_SIZE);
					if(delx>=0&&pos.y==j&&pos.z==k){//
						c_x=true;
					}
					if(dely>=0&&pos.x==i&&pos.z==k){//
						c_y=true;
					}
					if(delz>=0&&pos.x==i&&pos.y==j){//
						c_z=true;
					}
					if(delx>=0&&dely>=0&&delz>=0){
						if(sqrt((b->radius-delx)*(b->radius-delx)+
								(b->radius-dely)*(b->radius-dely)+
								(b->radius-delz)*(b->radius-delz))>=b->radius){
							collided=true;
							if((prev_pos.x>i&&del_pos.x<=0&&map->get_cube_type(i+1,j,k)==Cube::cubeNull)||
							   (prev_pos.x<i&&del_pos.x>=0&&map->get_cube_type(i-1,j,k)==Cube::cubeNull)){//
								c_x=true;
							}
							if((prev_pos.y>j&&del_pos.y<=0&&map->get_cube_type(i,j+1,k)==Cube::cubeNull)||
							   (prev_pos.y<j&&del_pos.y>=0&&map->get_cube_type(i,j-1,k)==Cube::cubeNull)){//
								c_y=true;
							}
							if((prev_pos.z>k&&del_pos.z<=0&&map->get_cube_type(i,j,k+1)==Cube::cubeNull)||
							   (prev_pos.z<k&&del_pos.z>=0&&map->get_cube_type(i,j,k-1)==Cube::cubeNull)){//
								c_z=true;
							}
						}
					}
				}
			}
		}
	}
	if(c_x){
		b->pos.x=b->prev_pos.x;
		b->vel.x*=-0.8;
		collided=true;
	}
	if(c_y){
		b->pos.y=b->prev_pos.y;
		b->vel.y*=-0.8;
		collided=true;
	}
	if(c_z){
		b->pos.z=b->prev_pos.z;
		b->vel.z*=-0.8;
		collided=true;
	}
	//if(collided){
		//b->pos=b->prev_pos;
	//}
	///*

	if(handle_stuck(b)){
		//std::cerr<<"stuck!!:"<<collided<<",c_x="<<c_x<<",c_y="<<c_y<<",c_z="<<c_z<<std::endl;
		collided=true;
	}

	//*/



	return collided;
}
bool MapRigidBody::check_stuck(physic::RigidBody* b){
	math::vec3<int> pos((b->pos.x)/Map::CUBE_SIZE,
			(b->pos.y)/Map::CUBE_SIZE,
			(b->pos.z)/Map::CUBE_SIZE);
	math::vec3<int> s(
			floor((b->pos.x-b->radius)/Map::CUBE_SIZE),
			floor((b->pos.y-b->radius)/Map::CUBE_SIZE),
			floor((b->pos.z-b->radius)/Map::CUBE_SIZE));
	math::vec3<int> e(
			ceil((b->pos.x+b->radius)/Map::CUBE_SIZE),
			ceil((b->pos.y+b->radius)/Map::CUBE_SIZE),
			ceil((b->pos.z+b->radius)/Map::CUBE_SIZE));
	float delx,dely,delz;
	for(int i=s.x;i<=e.x;i++){
		for(int j=s.y;j<=e.y;j++){
			for(int k=s.z;k<=e.z;k++){
				if(map->get_cube_type(i,j,k)!=Cube::cubeNull){
					delx=(0.5*Map::CUBE_SIZE+b->radius)-fabs(b->pos.x-(i+0.5)*Map::CUBE_SIZE);
					dely=(0.5*Map::CUBE_SIZE+b->radius)-fabs(b->pos.y-(j+0.5)*Map::CUBE_SIZE);
					delz=(0.5*Map::CUBE_SIZE+b->radius)-fabs(b->pos.z-(k+0.5)*Map::CUBE_SIZE);
					if(delx>=0&&pos.y==j&&pos.z==k){//
						return true;
					}
					if(dely>=0&&pos.x==i&&pos.z==k){//
						return true;
					}
					if(delz>=0&&pos.x==i&&pos.y==j){//
						return true;
					}
					if(delx>=0&&dely>=0&&delz>=0){
						if(sqrt((b->radius-delx)*(b->radius-delx)+
								(b->radius-dely)*(b->radius-dely)+
								(b->radius-delz)*(b->radius-delz))>=b->radius){
							return true;
						}
					}
				}
			}
		}
	}
	return false;
}
} /* namespace physic */
