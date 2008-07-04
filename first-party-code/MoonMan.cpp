#include "MoonMan.h"
#include "Log.h"
#include <stdlib.h>
#include <string.h>
#include "uGL.h"

#pragma warning (disable: 4996) //stfu, ho.

//-----------------
// Lua Methods
//-----------------
int CMoonMan::LuaPrint(lua_State *inLuaState)
{
	int theStackHeight = lua_gettop( inLuaState );
	for( int i=1; i<=theStackHeight; i++ )
	{
		const char* theMsg = lua_tostring(inLuaState, i );
		
		if( theMsg )
		{
			CLog::Print( const_cast<char*>(theMsg) );
		}
		else
		{
			(void) theMsg; // life sucks
		}
	}
	return 0;
}

//-----------------
// End Lua Methods
//-----------------

CMoonMan::CMoonMan()
{
	m_lua = luaL_newstate();
    lua_pushcfunction(m_lua, luaopen_math);
    lua_pushstring(m_lua, "math");
    lua_call(m_lua, 1, 0);	
    lua_pushcfunction(m_lua, luaopen_os);
    lua_pushstring(m_lua, "os");
    lua_call(m_lua, 1, 0);	
    lua_pushcfunction(m_lua, luaopen_table);
    lua_pushstring(m_lua, "table");
    lua_call(m_lua, 1, 0);	
    lua_pushcfunction(m_lua, luaopen_base);
    lua_pushstring(m_lua, "");
    lua_call(m_lua, 1, 0);	

	lua_register( m_lua, "print", &LuaPrint );

	// Parse the user's script
	if( 0 != luaL_dofile( m_lua, "main.lua" ) )
	{
		HandleError();	
	}

	DoLua( "initialize()" );
}

CMoonMan::~CMoonMan()
{
	lua_close( m_lua );
}

void CMoonMan::DoLua( char* inLua )
{
	if( 0 != luaL_dostring( m_lua, inLua ) )
	{
		HandleError();
	}
}

void CMoonMan::HandleError()
{
	int theStackHeight = lua_gettop( m_lua );
	for( int i=1; i<=theStackHeight; i++ )
	{
		int theType = lua_type( m_lua, i );
		switch( theType )
		{
			// string
			case 4:
				const char* theErrorMsg = lua_tostring(m_lua, i );
				// This is a good place to have a breakpoint for debugging the lua scripts
				CLog::Print( const_cast<char*>(theErrorMsg) );
			break;
		}
	}
}

void CMoonMan::Initialize()
{
}

void CMoonMan::Update()
{
	DoLua( "update()" );	
}

void CMoonMan::Keyboard( char* inString )
{
	DoLua( inString );
}

void CMoonMan::Render()
{
	lua_settop( m_lua, 0 );
	lua_getglobal( m_lua, "clearColor" );
	lua_rawgeti( m_lua, -1, 1 );
	float r = (float)lua_tonumber( m_lua, -1 );	lua_pop( m_lua, 1 );
	lua_rawgeti( m_lua, -1, 2 );
	float g = (float)lua_tonumber( m_lua, -1 );	lua_pop( m_lua, 1 );
	lua_rawgeti( m_lua, -1, 3 );
	float b = (float)lua_tonumber( m_lua, -1 );	lua_pop( m_lua, 1 );
	glClearColor( r, g, b, 1.f );

	lua_settop( m_lua, 0 );
	lua_getglobal( m_lua, "drawList" );
	int theItemCount = (int)lua_objlen( m_lua, -1 );
	for ( int theIndex = theItemCount; theIndex > 0; --theIndex )
	{
		lua_settop( m_lua, 1 );
		lua_rawgeti( m_lua, -1, theIndex );
		lua_getfield( m_lua, -1, "type" );
		const char* theType = lua_tostring( m_lua, -1 );
		if ( 0 == strcmp( "tristrip", theType ) )
		{
			lua_pop( m_lua, 1 );
			lua_getfield( m_lua, -1, "color" );
			lua_rawgeti( m_lua, -1, 1 );
			float r = (float)lua_tonumber( m_lua, -1 );	lua_pop( m_lua, 1 );
			lua_rawgeti( m_lua, -1, 2 );
			float g = (float)lua_tonumber( m_lua, -1 );	lua_pop( m_lua, 1 );
			lua_rawgeti( m_lua, -1, 3 );
			float b = (float)lua_tonumber( m_lua, -1 );	lua_pop( m_lua, 1 );
			glColor3f( r, g, b );

			lua_pop( m_lua, 1 );
			lua_getfield( m_lua, -1, "verts" );
			int theVertexCount = luaL_getn( m_lua, -1 );

			glBegin( GL_POLYGON );
			for ( int theVertIndex = 1; theVertIndex <= theVertexCount; ++theVertIndex )
			{
				lua_pushinteger( m_lua, theVertIndex );
				lua_gettable( m_lua, -2 );

				lua_pushinteger( m_lua, 1 );
				lua_gettable( m_lua, -2 );
				float x = (float)lua_tonumber( m_lua, -1 );
				lua_pop( m_lua, 1 );

				lua_pushinteger( m_lua, 2 );
				lua_gettable( m_lua, -2 );
				float y = (float)lua_tonumber( m_lua, -1 );
				lua_pop( m_lua, 1 );

				lua_pop( m_lua, 1 );

				glNormal3f( 0, 0, 1 );
				glVertex3f( x, y, 0 );
			}
			glEnd();

			lua_pop( m_lua, 1 );
		}
	}
}
