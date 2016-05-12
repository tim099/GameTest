#ifndef SOURCE_CLASS_DISPLAY_FONT_RENDERSTRING_H_
#define SOURCE_CLASS_DISPLAY_FONT_RENDERSTRING_H_
#include <string>
//#include <glm/vec2.hpp>
#include "class/tim/math/vec2.h"
namespace Display{
class RenderString {
public:
	static const float Font_Interval=0.65f;
	RenderString(std::string str,float char_size,math::vec2<float> pos=math::vec2<float>(0,0)
	,bool render_at_middle=false);
	virtual ~RenderString();
	math::vec2<float> font_size()const;
	static inline math::vec2<float> font_size(float size){
		return math::vec2<float>(size*Font_Interval,size);
	}
	math::vec2<float> string_size()const;
	static math::vec2<float> string_size(const std::string *str,float size);
	/*
	 * max_size define the max size of this string
	 */
	void auto_char_size(math::vec2<float> max_size);

	int insert_at;
	std::string str;
	float size;
	//glm::vec2 pos;
	math::vec2<float> pos;
	bool render_at_middle;
protected:

};
}
#endif /* SOURCE_CLASS_DISPLAY_FONT_RENDERSTRING_H_ */
