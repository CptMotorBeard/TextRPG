--[[
	--- Native Functions ---

	-- Visuals --
		void AddText(string text, int fontSize, float locX, float locY)
		void AddButton(string text, table [height, width, x, y] rect, string callbackName, table [r, g, b, a] backColour=Color::White)

	-- State Management --
		void PushGameState(string newState)
		void PopGameState()
		void PopGameStateHome()
		
	-- Engine Functions --
		table[width=, height=] GetScreenDimensions()
		void Shutdown()
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