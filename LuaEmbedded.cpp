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

	// Mylib
	lua_newtable(L);
	luaL_setfuncs(L, my_lib, 0);
	lua_setglobal(L, "mylib");
	luaL_dostring(L, "mylib.func(333)");



	// Execution of a lua string
	luaL_dostring(L, "print \"Helloes!\"");

	// Load a string and then execute it.
	luaL_loadstring(L, "io.write(\"Helloes again!\\n\")");
	lua_pcall(L, 0, LUA_MULTRET, 0);

	// Load from a file and then execute
	if (luaL_loadfile(L, "luascripts/helloworld.lua") == 0)
	{
		// File loaded call it
		lua_pcall(L, 0, LUA_MULTRET, 0);
	}

	// Close lua
	lua_close(L);

	std::cin.ignore();
    return 0;
}

