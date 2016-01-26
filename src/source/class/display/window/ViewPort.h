#ifndef SOURCE_CLASS_DISPLAY_WINDOW_VIEWPORT_H_
#define SOURCE_CLASS_DISPLAY_WINDOW_VIEWPORT_H_
#include <glm/vec2.hpp>
#include <GL/glew.h>
#include <GL/glfw3.h>
class ViewPort {
	static GLint x;
	static GLint y;
	static GLsizei width;
	static GLsizei height;
	static glm::ivec2 window_size;
public:
	static glm::ivec2 get_cur_window_size();
	static void set_window_size(glm::ivec2 size);
	static float get_cur_window_aspect();

	static float get_cur_viewport_aspect();
	static glm::ivec2 get_cur_viewport_size();

	static void set_viewport(GLint x, GLint y, GLsizei width, GLsizei height);
	ViewPort();
	virtual ~ViewPort();
};

#endif /* SOURCE_CLASS_DISPLAY_WINDOW_VIEWPORT_H_ */
