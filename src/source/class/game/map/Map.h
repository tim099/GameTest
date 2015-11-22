#ifndef MAP_H_
#define MAP_H_

class Map {
public:
	static const int MX=300,MY=70,MZ=300;
	Map();
	virtual ~Map();
	void load_map(const char *path);
	void set(int x,int y,int z,int val);
	int get(int x,int y,int z)const;

protected:
	int map[MX][MY][MZ];
};

#endif /* MAP_H_ */
