#ifndef WINDOW_H_
#define WINDOW_H_
class GLFWwindow;
//#include <glm/glm.hpp>
#include "class/tim/math/vec2.h"

//class HDC__;
//class HGLRC__;
#include "class/tim/globalObject/GlobalObject.h"
#include <string>
namespace Display{
class Window : public Tim::GlobalObject<Window>{
	static bool glewinitial;
	static bool glfwinitial;
public:
	Window(math::vec2<int> size,std::string name,bool full_screen);
	virtual ~Window();

	void set_veiwport();
	void creat_window(std::string name,bool full_screen);
	float get_aspect()const;
	int WindowShouldClose()const;
	void swap_buffer()const;
	void close_window();
	static math::vec2<int> get_screen_resolution();
	/*
	 * make current thread draw on this window
	 * must call render_off to release this window for other thread
	 */
	void render_on();

	/*
	 * release this window for other thread
	 */
	void render_off();
	math::vec2<int> get_size()const;
	GLFWwindow* get_window()const;

protected:
	void glewinit();
	void glfwinit();
	GLFWwindow* window;
	math::vec2<int> size;
	//HDC__ *dc;
	//HGLRC__ *lrc;
};
}

#endif /* WINDOW_H_ */
