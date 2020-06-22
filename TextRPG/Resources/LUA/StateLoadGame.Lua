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

function file_exists(name)
	local f=io.open(name,"r")
	if f~=nil then
		io.close(f)
		return true
	else
		return false
	end
end

function LuaLoad(source)
	source = tonumber(source)
	LoadGame(source)
end

function Build()
	
end

function GoBack()
	PopGameState()
end

function Render()
	AddText("Load Game State", 24, 10, 24)
	ScreenDimensions = GetScreenDimensions()

	rect = {}
	rect["width"] = 145
	rect["height"] = 30	
	
	padding = 15
	initialX = (ScreenDimensions["width"] / 2) - (rect["width"] / 2)
	initialY = (ScreenDimensions["height"] / 2)	- (rect["height"] / 2) - 100

	offset = padding + rect["height"]

	minFile = 0
	maxFile = 5

	for file = minFile, maxFile, 1
	do
		rect["x"] = initialX
		rect["y"] = initialY + (file * offset)

		--[ LUA files are found in Resources/LUA, save games are Resources/Saves/]
		savePath = "./Resources/Saves/File" .. tostring(file)
		if file_exists(savePath) then
			AddButton("Load Save", rect, "LuaLoad", tostring(file))
		else
			AddButton("No save found", rect)
		end
	end

	rect["x"] = initialX
	rect["y"] = initialY + ((maxFile + 2) * offset)
	AddButton("[LUA] Button BACK", rect, "GoBack");
end