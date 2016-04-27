#ifndef SOURCE_CLASS_DISPLAY_FONT_RENDERSTRING_H_
#define SOURCE_CLASS_DISPLAY_FONT_RENDERSTRING_H_
#include <string>
#include <glm/vec2.hpp>
namespace Display{
class RenderString {
public:
	static const float Font_Interval=0.65f;
	RenderString(std::string str,float char_size,glm::vec2 pos=glm::vec2(0,0),bool render_at_middle=false);
	virtual ~RenderString();
	glm::vec2 font_size()const;
	static inline glm::vec2 font_size(float size){
		return glm::vec2(size*Font_Interval,size);
	}
	glm::vec2 string_size()const;
	static glm::vec2 string_size(const std::string *str,float size);
	/*
	 * max_size define the max size of this string
	 */
	void auto_char_size(glm::vec2 max_size);

	int insert_at;
	std::string str;
	float size;
	glm::vec2 pos;
	bool render_at_middle;
protected:

};
}
#endif /* SOURCE_CLASS_DISPLAY_FONT_RENDERSTRING_H_ */
