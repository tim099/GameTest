#include "class/tim/lua/Lua.h"
#include <iostream>
/*
extern "C"
{
    #include "lua/lua.h"
    #include "lua/lauxlib.h"
    #include "lua/lualib.h"
}
*/
namespace Tim {

Lua::Lua() {
	L=luaL_newstate();
	luaL_openlibs(L);
}
Lua::~Lua() {
	lua_close(L);
}
bool Lua::loadfile(std::string path){
	int bRet = luaL_loadfile(L,path.c_str());
    if(bRet){
        std::cout<<"Lua::loadfile error,file path:"<<path<<std::endl;
        return false;
    }
    return true;
}
void Lua::rigister_function(std::string name,int(*func)(lua_State *L)){
	lua_register(L,name.c_str(),func);
}
bool Lua::p_call(int parameter_num,int return_num,int errfunc){
	int bRet= lua_pcall(L,parameter_num,return_num,errfunc);
    if(bRet){
        std::cout<<"Lua::p_call error"<<std::endl;
        return false;
    }
    return true;
}
std::string Lua::get_string(std::string name){
    lua_getglobal(L,"str");
    std::string str=lua_tostring(L,-1);
    lua_pop(L,1);//pop string create by lua_tostring on the top
    return str;
}
void Lua::set_global(std::string name){
	lua_setglobal(L,name.c_str());
}
void Lua::get_global(std::string name){
	lua_getglobal(L,name.c_str());
}
void Lua::push_number(int num){
	lua_pushnumber(L,num);
}
void Lua::pushlightuserdata(void *ptr){
	lua_pushlightuserdata(L,ptr);
}
void *Lua::get_userdata(int at){
	void *ptr=lua_touserdata(L,at);
	lua_pop(L,1);//pop ptr create by lua_touserdata on the top
	return ptr;
}
int Lua::get_number(int at){
	int num=lua_tonumber(L,at);
	lua_pop(L,1);//pop int create by lua_tonumber on the top
	return num;
}
int Lua::to_number(int at){
	return lua_tonumber(L,at);
}
void Lua::pop(int n){
	lua_pop(L,n);
}
void Lua::get_table(std::vector<int> &table){
	if(lua_istable(L, -1)){
		lua_pushnil(L);
		while(lua_next(L, -2)){
			table.push_back(lua_tonumber(L, -1));
			pop(1);
		}
	}else{
		std::cout<<"Lua::get_table error, not a table"<<std::endl;
	}
}
} /* namespace Tim */
