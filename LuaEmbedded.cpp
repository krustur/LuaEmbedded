// LuaEmbedded.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "luasrc/lua.h"
#include "luasrc/lualib.h"
#include "luasrc/lauxlib.h"

static int my_func(lua_State *L)
{
	lua_Integer in = luaL_checkinteger(L, 1);
	printf("Helloes from C from LUA [%d]!\n", in);
	lua_pushinteger(L, 666);

	return 1;
}

static const luaL_Reg my_lib[] = {
	{ "func",   my_func },
	{ NULL, NULL }
};

int main()
{
	// Open lua
	//lua_State *L = lua_open();
	lua_State *L = luaL_newstate();

	// Load the libraries
	luaL_openlibs(L);

	// mylib - without merge
	//lua_newtable(L);
	//luaL_setfuncs(L, my_lib, 0);
	//lua_setglobal(L, "mylib");
	
	// mylib - with merge
	lua_getglobal(L, "mylib");
	if (lua_isnil(L, -1)) {
		lua_pop(L, 1);
		lua_newtable(L);
	}
	luaL_setfuncs(L, my_lib, 0);
	lua_setglobal(L, "mylib");
	
	// mylib test
	luaL_dostring(L, "mylib.func(333)");

	// Execution of a lua string
	luaL_dostring(L, "print (\"Helloes!\")");

	// Load a string and then execute it.
	luaL_loadstring(L, "io.write(\"Helloes again!\\n\")");
	lua_pcall(L, 0, LUA_MULTRET, 0);

	// Load from a file and then execute
	if (luaL_loadfile(L, "luascripts/helloworld.lua") == 0)
	{
		// File loaded call it
		lua_pcall(L, 0, LUA_MULTRET, 0);
	}

	// mylib test - again
	luaL_dostring(L, "mylib.func(111)");

	// myluafunc
	luaL_dostring(L, "function myfunc ( x )\n	print (string.format(\"Helloes from LUA from C [%d]!\", x))\n	return x-1\nend\n");
	//luaL_dostring(L, "myfunc(222)\n");
	
	// myluafunc - test
	lua_getglobal(L, "myfunc");	
	lua_pushnumber(L, 999);	
	lua_call(L, 1, 1);// call the function with 1 arguments, return 1 result
	int out = (int)lua_tointeger(L, -1);
	lua_pop(L, 1);
	printf("LUA returned [%d]!\n", out);

	// Close lua
	lua_close(L);

	std::cin.ignore();
    return 0;
}

