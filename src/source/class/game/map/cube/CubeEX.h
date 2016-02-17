#ifndef SOURCE_CLASS_GAME_MAP_CUBE_CUBEEX_H_
#define SOURCE_CLASS_GAME_MAP_CUBE_CUBEEX_H_
/*
 * extra cube type for cubes like building ,trees ..etc
 */
class CubeEX {
public:
	CubeEX();
	virtual ~CubeEX();
	virtual void draw();
	void set_pos(int x,int y,int z);
	int type;
protected:
	int x,y,z;
};

#endif /* SOURCE_CLASS_GAME_MAP_CUBE_CUBEEX_H_ */
