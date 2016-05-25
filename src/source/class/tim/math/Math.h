#ifndef MATH_H_
#define MATH_H_
#include <glm/glm.hpp>
#include "class/tim/math/vec2.h"
#define Max(a,b) a>b?a:b
#define Min(a,b) a<b?a:b
namespace Tim {

class Math {
public:
	Math();
	virtual ~Math();
	static float max(glm::vec3 v);

	static glm::vec2 max(glm::vec2 a,glm::vec2 b);
	static glm::vec2 min(glm::vec2 a,glm::vec2 b);
	static int get_val_at(int val,int at);
	static int get_len(int val);
	static glm::vec2 get_size(float width,float aspect);
	static glm::mat4 BiasMat();
	static float aspect(glm::ivec2 size);
	static float aspect(math::vec2<int> size);

	static int pow(int base,int power);
	static float fit_in_maxsize(math::vec2<float> size,math::vec2<float> maxsize);
	static glm::vec2 convert_to_texcoord(glm::vec2 pos);
	static glm::vec2 convert_to_wincoord(glm::vec2 pos);
};

} /* namespace Tim */

#endif /* MATH_H_ */
