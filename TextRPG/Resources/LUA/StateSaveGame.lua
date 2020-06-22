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

function LuaSave(source)
	source = tonumber(source)
	SaveGame(source)

	RefreshState()
end

function Build()
	
end

function GoBack()
	PopGameState()
end

function Render()
	AddText("Save Game State", 24, 10, 24)
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

		savePath = "./Resources/Saves/File" .. tostring(file)
		if file_exists(savePath) then
			AddButton("Overwrite Save", rect, "LuaSave", tostring(file))
		else
			AddButton("New Save", rect, "LuaSave", tostring(file))
		end
	end

	rect["x"] = initialX
	rect["y"] = initialY + ((maxFile + 2) * offset)
	AddButton("[LUA] Button BACK", rect, "GoBack");
end