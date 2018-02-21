// LuaEmbedded.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "luasrc/lua.h"
#include "luasrc/lualib.h"
#include "luasrc/lauxlib.h"

int main()
{
	// Open lua
	//lua_State *L = lua_open();
	lua_State *L = luaL_newstate();

	// Load the libraries
	luaL_openlibs(L);
	//luaL_Reg(L);

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

