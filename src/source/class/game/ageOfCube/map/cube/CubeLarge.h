#ifndef SOURCE_CLASS_GAME_AGEOFCUBE_MAP_CUBE_CUBELARGE_H_
#define SOURCE_CLASS_GAME_AGEOFCUBE_MAP_CUBE_CUBELARGE_H_

#include "class/game/ageOfCube/map/cube/CubeEX.h"
#include "class/game/ageOfCube/map/cube/AttachCube.h"
#include "class/tim/math/vec3.h"
#include "class/tim/math/vec2.h"
#include <vector>
namespace AOC {
class Map;
class CubeLarge: public CubeEX {
public:
	CubeLarge();
	virtual ~CubeLarge();
	virtual void remove_cubeEX();

	virtual math::vec3<int> get_cube_large_size(){
		return math::vec3<int>(1,1,1);
	}
	//return the cube that CubeLarge take place,except the original place(0,0,0)
	virtual void get_attach_cube(std::vector<AttachCube*> &attach_cubes){
		math::vec3<int> size=get_cube_large_size();
		for(int i=0;i<size.x;i++){
			for(int j=0;j<size.y;j++){
				for(int k=0;k<size.z;k++){
					if(!(i==0&&j==0&&k==0)){
						attach_cubes.push_back(new AttachCube(i,j,k,this));
					}
				}
			}
		}
	}
	//the ground that should build on
	virtual void get_build_on(std::vector<math::vec3<int> > &build_on){
		math::vec3<int> size=get_cube_large_size();
		for(int i=0;i<size.x;i++){
			for(int j=0;j<size.z;j++){
				build_on.push_back(math::vec3<int>(i,-1,j));
			}
		}
	}
	virtual void get_build_on_type(std::vector<int> &v){
		//if v==empty then means build on all basic cube
	}
	bool buildable(int x,int y,int z);
	bool create_cube_large(int x,int y,int z);
	bool removing;
	int x,y,z;
protected:
	std::vector<AttachCube*> attach_cubes;

};

} /* namespace AOC */

#endif /* SOURCE_CLASS_GAME_AGEOFCUBE_MAP_CUBE_CUBELARGE_H_ */
