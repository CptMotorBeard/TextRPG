#include "LUA.h"
#include "GameStates.h"

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
	// (string text, table [height, width, x, y] rect, function callback, table [r, g, b, a] backColour)
	// (table[string, fontSize, table [r, g, b, a] fontColour, table [r, g, b, a] fontOutline] text, table [height, width, x, y] rect, function callback, table [r, g, b, a] backColour)

	return 0;
}

/// <summary> void PushGameState(State* newState) </summary>
int lua_PushGameState(lua_State* L)
{
	if (lua_gettop(L) >= 1)
	{
		State* s = static_cast<State *>(lua_touserdata(L, 1));
		if (s != NULL)
		{
			StateType t = s->GetStateType();

			switch (t)
			{
			case StateType::StateMainMenu:
				StateManager::GetInstance()->PushState(StateMainMenu());
				break;
			case StateType::StateFactionCreation:
				StateManager::GetInstance()->PushState(StateFactionCreation());
				break;
			case StateType::StateFactionOverview:
				StateManager::GetInstance()->PushState(StateCharacterOverview());
				break;
			case StateType::StateCharacterCreation:
				StateManager::GetInstance()->PushState(StateCharacterCreation());
				break;
			case StateType::StateCharacterOverview:
				StateManager::GetInstance()->PushState(StateCharacterOverview());
				break;
			case StateType::StateLoadGame:
				StateManager::GetInstance()->PushState(StateLoadGame());
				break;
			case StateType::StateSaveGame:
				StateManager::GetInstance()->PushState(StateSaveGame());
				break;
			default:
				break;
			}
		}
	}

	return 0;
}

/// <summary> State* GetStateSaveGame() </summary>
int lua_GetStateSaveGame(lua_State* L)
{
	lua_pushlightuserdata(L, new StateSaveGame());
	return 1;
}
#pragma endregion

void LuaManager::InitializeNativeFunctions()
{
	lua_register(L, "AddText", lua_AddText);
	lua_register(L, "AddButton", lua_AddButton);

	lua_register(L, "PushGameState", lua_PushGameState);
	lua_register(L, "GetStateSaveGame", lua_GetStateSaveGame);
}

void LuaManager::Shutdown()
{
	lua_close(L);
}