#ifndef WINDOW_H_
#define WINDOW_H_
class GLFWwindow;
#include <glm/glm.hpp>


class HDC__;
class HGLRC__;
#include "class/tim/globalObject/GlobalObject.h"
class Window : public Tim::GlobalObject<Window>{
	static bool glewinitial;
	static bool glfwinitial;
public:
	Window(glm::ivec2 size,const char* name,bool full_screen);
	virtual ~Window();

	void set_veiwport();
	void creat_window(const char* name,bool full_screen);
	float get_aspect()const;
	int WindowShouldClose()const;
	void swap_buffer()const;
	void close_window();
	/*
	 * make current thread draw on this window
	 * must call render_off to release this window for other thread
	 */
	void render_on();

	/*
	 * release this window for other thread
	 */
	void render_off();
	glm::ivec2 get_size()const;
	GLFWwindow* get_window()const;

protected:
	void glewinit();
	void glfwinit();
	GLFWwindow* window;
	glm::ivec2 size;
	HDC__ *dc;
	HGLRC__ *lrc;
};


#endif /* WINDOW_H_ */
