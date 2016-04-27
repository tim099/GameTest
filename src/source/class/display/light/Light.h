#ifndef LIGHT_H_
#define LIGHT_H_
//#include <GL/glew.h>
namespace Display{
class Light {
public:
	Light(bool shadow);
	virtual ~Light();
	bool shadow;
};
}
#endif /* LIGHT_H_ */
