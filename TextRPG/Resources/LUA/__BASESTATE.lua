--[[
	--- Native Functions ---

	-- Visuals --
		void AddText(string text, int fontSize, float locX, float locY)
		void AddButton(string text, table [height, width, x, y] rect, string callbackName, table [r, g, b, a] backColour=Color::White)

	-- State Management --
		void PushGameState(string newState)
		void PopGameState()
		void PopGameStateHome()
		
	-- ImGui --
		void ImGuiBegin(string title)
		void ImGuiEnd()
		
	-- Engine Functions --
		table[width=, height=] GetScreenDimensions()
		void Shutdown()
]]--

function Build()
	
end

function Render()

end