--[[
	--- Native Functions ---

	-- Visuals --
		void AddText(string text, int fontSize, float locX, float locY)
		void AddButton(string text, table [height, width, x, y] rect, string callbackName, table [r, g, b, a] backColour=Color::White)

	-- State Management --
		void PushGameState(State* newState)
		State* GetStateSaveGame()
]]--

function Build()
	
end

function GotoSaveGame()
	print "[LUA] button callback"
	PushGameState(GetStateSaveGame())
end

function PreRender()
	AddText("Main Menu State", 24, 10, 24)

	rect = {}
	rect["height"] = 50
	rect["width"] = 200
	rect["x"] = 100
	rect["y"] = 100

	AddButton("[LUA] Button", rect, "GotoSaveGame");
end

function PostRender()
	
end