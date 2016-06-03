#ifndef MOUSE_H_
#define MOUSE_H_
#include <GL/glew.h>
#include <GL/glfw3.h>
#include <glm/glm.hpp>
#include "class/tim/math/vec2.h"
namespace Display{
class FrameBuffer;
}
namespace Input{
class Mouse {
	static Mouse *rigister_mouse;
public:
	Mouse();
	virtual ~Mouse();
	static Mouse *get_cur_mouse();
	static void cursor_pos_callback(GLFWwindow* window, double x, double y);
	static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
	static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
	void callback_rigister(GLFWwindow *window);

	void cursor_pos_input(GLFWwindow* window, double x, double y);
	void scroll_input(GLFWwindow* window,double xoffset,double yoffset);
	void mouse_button_input(GLFWwindow* window, int button, int action, int mods);

	void clear();
	void update();
	glm::vec2 get_screen_space_pos(math::vec2<int> screen_size);

	glm::vec2 get_tex_space_pos();

	glm::vec3 get_world_space_pos(Display::FrameBuffer* FBO,glm::mat4 inverseMat);


	glm::ivec2 pos_delta()const;
	glm::vec2 get_screen_pos_delta()const;

	glm::ivec2 pos;
	glm::ivec2 prev_pos;
	glm::ivec2 _pos_delta;
	glm::vec2 screen_pos;
	glm::vec2 prev_screen_pos;
	glm::vec3 world_pos;
	double scroll;
	/*left is the mouse left key,value=true if being pressed
	 *right is the mouse right key,value=true if being pressed
	 *and middle is the scroll,value=true if being pressed
	 */

	bool left_pressed()const;
	bool right_pressed()const;
	bool mid_pressed()const;

	bool left_clicked()const;
	bool right_clicked()const;
	bool mid_clicked()const;

	bool get_left_click();
	bool get_right_click();
	bool get_mid_click();
protected:
	bool left,right,mid;
	bool left_click,right_click,mid_click;
};
}
#endif /* MOUSE_H_ */
