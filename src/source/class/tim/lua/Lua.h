#ifndef SOURCE_CLASS_TIM_LUA_LUA_H_
#define SOURCE_CLASS_TIM_LUA_LUA_H_
#include "lua/lua.hpp"
//#include "luajit/lua.hpp"
#include <vector>
#include <string>
namespace Tim {

class Lua {
public:
	Lua();
	virtual ~Lua();
	bool loadfile(std::string path);
	void rigister_function(std::string name,int(*func)(lua_State *L));
	bool p_call(int parameter_num,int return_num,int errfunc=0);

	void get_global(std::string name);
	void set_global(std::string name);
	void get_table(std::vector<int> &table);
	void *get_userdata(int at);
	void pushlightuserdata(void *ptr);
	void push_number(int num);
	void pop(int n);

	int to_number(int at);
	int get_number(int at);
	std::string get_string(std::string name);
	lua_State *L;
};

} /* namespace Tim */

#endif /* SOURCE_CLASS_TIM_LUA_LUA_H_ */
