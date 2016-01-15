#ifndef MATH_H_
#define MATH_H_
#include <glm/glm.hpp>
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
	static glm::mat4 BiasMat();
	static float aspect(glm::ivec2 size);
	static int pow(int base,int power);
	static glm::vec2 convert_to_texcoord(glm::vec2 pos);
	static glm::vec2 convert_to_wincoord(glm::vec2 pos);
};

} /* namespace Tim */

#endif /* MATH_H_ */
