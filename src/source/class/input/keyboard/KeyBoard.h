#ifndef KEYBOARD_H_
#define KEYBOARD_H_
#include <GL/glew.h>
#include <GL/glfw3.h>
#include <set>
class KeyBoard {
public:
	KeyBoard();
	virtual ~KeyBoard();
	void inputkey(GLFWwindow *window,int key,int scancode,int action,int mods);
	bool pressed(int key);
	bool get(int key);
	void tic();
protected:
	void key_press(int key,int scancode,int mods);
	void key_release(int key,int scancode,int mods);
	void key_repeat(int key,int scancode,int mods);
	std::set<int>keys;
};

#endif /* KEYBOARD_H_ */
