#ifndef OBJ_H_
#define OBJ_H_
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>
#include <cstdio>
#include <class/display/model/obj/Face.h>
namespace Display{
class Model;

class Obj{
public:
	Obj();
	virtual ~Obj();
	static Obj* load_obj(const char* path);
    std::vector<glm::vec3>v;
    std::vector<glm::vec2>uv;
    std::vector<glm::vec3>vn;
    std::vector<Face>fs;
protected:


};
}
#endif /* OBJ_H_ */
