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

function GoBack()
	PopGameState()
end

function Render()
	AddText("Character Overview State", 24, 10, 24)
	ScreenDimensions = GetScreenDimensions()

	rect = {}
	rect["width"] = 145
	rect["height"] = 30	
	
	initialX = (ScreenDimensions["width"] / 2) - (rect["width"] / 2)
	initialY = (ScreenDimensions["height"] / 2)	- (rect["height"] / 2)

	rect["x"] = initialX
	rect["y"] = initialY
	AddButton("[LUA] Button BACK", rect, "GoBack");
end