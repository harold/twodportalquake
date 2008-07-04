#include "LuaIncludes.h"

//-----------------------------------------------------------------
// The MoonMan encapsulates the lua functionality. Lua means moon
// in portugese, get it? hrhrhr.
//
// It holds the pointer to the lua state.
//
// It also has some rudimentary error handling to help debug
// the user's lua code.
//
// It also handles making the lua 'callbacks'
//   - Initialize, Update, and Keyboard
//
// It also implements the static methods that get wired up to
// luacfunctions so they can be called from the inside
//-----------------------------------------------------------------

class CMoonMan
{
	private:
		lua_State* m_lua;

	private:
		// This is the primary way the moon man gets things done in lua.
		// Calling DoLua sets up the error handling.
		void DoLua( char* inLua );
		void HandleError();

	public:
		// Called from the outside at the appropriate times to initiate lua 'callbacks'
		void Initialize();
		void Update();
		void Keyboard( char* inString );

		void Render();

	public:
		CMoonMan();
		~CMoonMan();

	private: // Lua methods
		static int LuaPrint( lua_State* inLuaState );
};