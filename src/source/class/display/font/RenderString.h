#ifndef SOURCE_CLASS_DISPLAY_FONT_RENDERSTRING_H_
#define SOURCE_CLASS_DISPLAY_FONT_RENDERSTRING_H_
#include <string>
#include <glm/glm.hpp>

class RenderString {
public:
	static const float Font_Interval=0.7f;
	RenderString(std::string str,float char_size,glm::vec2 pos=glm::vec2(0,0),bool render_at_middle=false);
	virtual ~RenderString();
	glm::vec2 font_size()const;
	glm::vec2 string_size()const;
	std::string str;
	float size;
	glm::vec2 pos;
	bool render_at_middle;
protected:

};

#endif /* SOURCE_CLASS_DISPLAY_FONT_RENDERSTRING_H_ */
