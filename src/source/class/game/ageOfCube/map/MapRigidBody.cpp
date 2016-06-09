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
bool MapRigidBody::check_collision(physic::RigidBody* b,bool &c_x,bool &c_y,bool &c_z,Cube* &collide_cube){
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

	collide_cube=0;
	c_x=false,c_y=false,c_z=false;
	float delx,dely,delz;
	for(int i=s.x;i<=e.x;i++){
		for(int j=s.y;j<=e.y;j++){
			for(int k=s.z;k<=e.z;k++){
				if(map->get_cube_type(i,j,k)!=Cube::cubeNull){
					delx=(0.5*Map::CUBE_SIZE+b->radius)-fabs(b->pos.x-(i+0.5)*Map::CUBE_SIZE);
					dely=(0.5*Map::CUBE_SIZE+b->radius)-fabs(b->pos.y-(j+0.5)*Map::CUBE_SIZE);
					delz=(0.5*Map::CUBE_SIZE+b->radius)-fabs(b->pos.z-(k+0.5)*Map::CUBE_SIZE);
					if(delx>=0&&pos.y==j&&pos.z==k){
						collided=true;
						c_x=true;
						collide_cube=map->get_cube(i,j,k);
					}
					if(dely>=0&&pos.x==i&&pos.z==k){
						collided=true;
						c_y=true;
						collide_cube=map->get_cube(i,j,k);
					}
					if(delz>=0&&pos.x==i&&pos.y==j){
						collided=true;
						c_z=true;
						collide_cube=map->get_cube(i,j,k);
					}

					if(delx>=0&&dely>=0&&delz>=0){
						double bx=b->radius-delx,by=b->radius-dely,bz=b->radius-delz;
						if(bx<0)bx=0;if(by<0)by=0;if(bz<0)bz=0;
						if(sqrt(bx*bx+by*by+bz*bz)<=b->radius){
							collided=true;
							collide_cube=map->get_cube(i,j,k);
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
	return collided;
}
bool MapRigidBody::MapRigidBody::check_collision(physic::RigidBody* b){
	id=0;
	bool c_x=false,c_y=false,c_z=false;
	bool c_x_col=false,c_y_col=false,c_z_col=false;
	Cube* collide_cube=0;
	bool collision=false;;
	bool collided=check_collision(b,c_x,c_y,c_z,collide_cube);
	if(collided)collision=true;
	for(int i=0;i<3&&collided;i++){
		if(!c_x_col&&c_x){
			b->pos.x=b->prev_pos.x;
			b->vel.x*=-0.8;
			c_x_col=true;
		}
		if(!c_y_col&&c_y){
			b->pos.y=b->prev_pos.y;
			b->vel.y*=-0.8;
			c_y_col=true;
		}
		if(!c_z_col&&c_z){
			b->pos.z=b->prev_pos.z;
			b->vel.z*=-0.8;
			c_z_col=true;
		}
		if(collide_cube){
			collide_cube->collide(b);
		}
		if(Building* building=dynamic_cast<Building*>(collide_cube)){
			//std::cout<<"map_rigid_body colli at building!!="<<building->get_name()<<std::endl;
			id=(building->get_id());
		}
		collided=check_collision(b,c_x,c_y,c_z,collide_cube);
	}


	if(handle_stuck(b)){
		//std::cerr<<"stuck!!:"<<collided<<",c_x="<<c_x<<",c_y="<<c_y<<",c_z="<<c_z<<std::endl;
		collided=true;
	}


	return collision;
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
						double bx=b->radius-delx,by=b->radius-dely,bz=b->radius-delz;
						if(bx<0)bx=0;if(by<0)by=0;if(bz<0)bz=0;
						if(sqrt(bx*bx+by*by+bz*bz)<=b->radius){
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
