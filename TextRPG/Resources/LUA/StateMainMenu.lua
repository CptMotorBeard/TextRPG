--[[
	--- Native Functions ---

	-- Visuals --
		void AddText(string text, int fontSize, float locX, float locY)
		void AddButton(string text, table [height, width, x, y] rect, string callbackName)
		void AddButton(string text, table [height, width, x, y] rect, string callbackName, string callbackSource) -- The callbackSource is passed as an argument to callbacks

	-- State Management --
		[STATES]:
			MainMenu
			FactionCreation
			FactionOverview
			CharacterCreation
			CharacterOverview
			LoadGame
			SaveGame
			WorldOverview
			Diplomacy
			Combat
			Inventory
			CityUpgrades
			BuildingUpgrades
			UnitUpgrades
	
		void PushGameState(string newState)
		void PopGameState()
		void PopGameStateHome()
		
	-- Game Management --
		void SaveGame(int saveFile)
		void LoadGame(int saveFile)
		
	-- ImGui --
		void ImGuiBegin(string title)
		void ImGuiEnd()
		
	-- Engine Functions --
		Unit CreateNewUnit()
		Leader CreateNewLeader()
		table[width=, height=] GetScreenDimensions()
		void Shutdown()
		void RefreshState()
]]--

function Build()

end

function GoToNewGame()
	print "[LUA] button callback"
	PushGameState("CharacterCreation")
end

function GoToSaveGame()
	print "[LUA] button callback"
	PushGameState("SaveGame")
end

function GoToLoadGame()
	print "[LUA] button callback"
	PushGameState("LoadGame")
end

function QuitGame()
	print "[LUA] button callback"
	file = io.open("test9001.tmp", "w")
	file:write("ttt")
	file:close()
	Shutdown()
end

function Render()
	AddText("Main Menu State", 24, 10, 24)
	ScreenDimensions = GetScreenDimensions()

	rect = {}
	rect["width"] = 145
	rect["height"] = 30	
	
	padding = 15
	initialX = (ScreenDimensions["width"] / 2) - (rect["width"] / 2)
	initialY = (ScreenDimensions["height"] / 2)	- (rect["height"] / 2)

	offset = padding + rect["height"]

	rect["x"] = initialX
	rect["y"] = initialY
	AddButton("[LUA] Button New", rect, "GoToNewGame");

	rect["x"] = initialX
	rect["y"] = initialY + (offset)
	AddButton("[LUA] Button Save", rect, "GoToSaveGame");

	rect["x"] = initialX
	rect["y"] = initialY + (2 * offset)
	AddButton("[LUA] Button Load", rect, "GoToLoadGame");

	rect["x"] = initialX
	rect["y"] = initialY + (3 * offset)
	AddButton("[LUA] Button Quit", rect, "QuitGame");
end