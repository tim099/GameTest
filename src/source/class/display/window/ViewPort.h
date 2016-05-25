#ifndef SOURCE_CLASS_DISPLAY_WINDOW_VIEWPORT_H_
#define SOURCE_CLASS_DISPLAY_WINDOW_VIEWPORT_H_
//#include <glm/vec2.hpp>
#include <GL/glew.h>
#include <GL/glfw3.h>
#include "class/tim/math/vec2.h"
namespace Display{
class ViewPort {
	static GLint x;
	static GLint y;
	static GLsizei width;
	static GLsizei height;
	static math::vec2<int> window_size;
public:
	static math::vec2<int> get_cur_window_size();
	static void set_window_size(math::vec2<int> size);
	static float get_cur_window_aspect();

	static float get_cur_viewport_aspect();
	static math::vec2<int> get_cur_viewport_size();

	static void set_viewport(GLint x, GLint y, GLsizei width, GLsizei height);
	ViewPort();
	virtual ~ViewPort();
};
}
#endif /* SOURCE_CLASS_DISPLAY_WINDOW_VIEWPORT_H_ */
