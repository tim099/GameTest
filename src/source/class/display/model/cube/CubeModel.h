#ifndef CUBEMODEL_H_
#define CUBEMODEL_H_
#include <class/display/model/Model.h>
class CubeModel{
public:
	CubeModel(double size=0.5);
	virtual ~CubeModel();
	static Model *CubeSide(int i,double size);
	Model* cube[6];
protected:

};

#endif /* CUBEMODEL_H_ */
