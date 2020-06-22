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

function Render()

end