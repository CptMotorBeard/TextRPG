#include "LUA.h"
#include "GameStates.h"
#include "GameStateFactoryManager.h"
#include "SFML-manager.h"

lua_State *LuaManager::L = nullptr;

bool LuaManager::LuaOkay(lua_State* L, int r)
{
	if (r != LUA_OK)
	{
		std::string errorMessage = lua_tostring(L, -1);
		std::cout << errorMessage << std::endl;

		return false;
	}

	return true;
}

lua_State* LuaManager::GetLuaState()
{
	if (LuaManager::L == nullptr)
	{
		L = luaL_newstate();
		luaL_openlibs(L);
		InitializeNativeFunctions();
	}

	return L;
}

bool LuaManager::CallbackFunction(std::string functionName, const char* sourceFile)
{
	if (LuaManager::LuaOkay(L, luaL_dofile(L, sourceFile)))
	{
		lua_getglobal(L, functionName.c_str());
		if (lua_isfunction(L, -1))
		{
			return LuaManager::LuaOkay(L, lua_pcall(L, 0, 0, 0));
		}
	}

	return false;
}

#pragma region Native Functions

/// <summary> void AddText(string text, int fontSize, float locX, float locY) </summary>
int lua_AddText(lua_State* L)
{
	if (lua_gettop(L) >= 4)
	{
		std::string text = lua_tostring(L, 1);
		int fontSize = (int)lua_tonumber(L, 2);
		float locx = (float)lua_tonumber(L, 3);
		float locy = (float)lua_tonumber(L, 4);

		StateManager::GetInstance()->GetCurrentState()->AddText(text, fontSize, locx, locy);
	}

	return 0;
}

int lua_AddButton(lua_State* L)
{
	// (string text, table [height, width, x, y] rect, string callbackName, table [r, g, b, a] backColour)
	// (table[string, fontSize, table [r, g, b, a] fontColour, table [r, g, b, a] fontOutline] text, table [height, width, x, y] rect, string callbackName, table [r, g, b, a] backColour)

	std::string text = lua_tostring(L, 1);
	// Table for Rect
	lua_getfield(L, 2, "height");
	float height = (float)lua_tonumber(L, -1);
	lua_getfield(L, 2, "width");
	float width = (float)lua_tonumber(L, -1);
	lua_getfield(L, 2, "x");
	float locx = (float)lua_tonumber(L, -1);
	lua_getfield(L, 2, "y");
	float locy = (float)lua_tonumber(L, -1);

	std::string callbackName = lua_tostring(L, 3);

	StateManager::GetInstance()->GetCurrentState()->AddButton(text, sf::FloatRect(locx, locy, width, height), callbackName);

	return 0;
}

/// <summary> void PushGameState(string newState) </summary>
int lua_PushGameState(lua_State* L)
{
	if (lua_gettop(L) >= 1)
	{
		std::string state = lua_tostring(L, 1);

		State* newState = GameStateFactoryManager::GetInstance()->Create(state);
		StateManager::GetInstance()->PushState(*newState);
	}

	return 0;
}

/// <summary> void PopGameState() </summary>
int lua_PopGameState(lua_State* L)
{
	StateManager::GetInstance()->PopState();

	return 0;
}

/// <summary> void PopGameStateHome() </summary>
int lua_PopGameStateHome(lua_State* L)
{
	StateManager::GetInstance()->PopToBottom();

	return 0;
}

int lua_Shutdown(lua_State* L)
{
	SFML_Manager::GetInstance()->Window.close();
	return 0;
}
#pragma endregion

void LuaManager::InitializeNativeFunctions()
{
	// SFML calls
	lua_register(L, "AddText", lua_AddText);
	lua_register(L, "AddButton", lua_AddButton);

	// State Calls
	lua_register(L, "PushGameState", lua_PushGameState);
	lua_register(L, "PopGameState", lua_PopGameState);
	lua_register(L, "PopGameStateHome", lua_PopGameStateHome);

	// Engine calls
	lua_register(L, "Shutdown", lua_Shutdown);
}

void LuaManager::Shutdown()
{
	lua_close(L);
}