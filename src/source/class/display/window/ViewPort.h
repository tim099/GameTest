#ifndef SOURCE_CLASS_DISPLAY_WINDOW_VIEWPORT_H_
#define SOURCE_CLASS_DISPLAY_WINDOW_VIEWPORT_H_
#include <glm/glm.hpp>
class ViewPort {
public:
	static float get_cur_viewport_aspect();
	static glm::ivec2 get_cur_viewport_size();
	ViewPort();
	virtual ~ViewPort();
};

#endif /* SOURCE_CLASS_DISPLAY_WINDOW_VIEWPORT_H_ */
