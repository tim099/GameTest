#ifndef CUBEMODEL_H_
#define CUBEMODEL_H_
#include "class/display/model/Model.h"
namespace Display{
class CubeModel{
public:
	CubeModel(double size=0.5);
	CubeModel(double sx,double sy,double sz);
	virtual ~CubeModel();
	static Model *CubeSide(int i,double size);
	static Model *CubeSide(int i,double sx,double sy,double sz);
	Display::Model* cube[6];
protected:

};
}
#endif /* CUBEMODEL_H_ */
