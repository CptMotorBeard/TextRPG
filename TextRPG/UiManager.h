#pragma once
#include "BaseIncludes.h"
#include <Ultralight/Ultralight.h>

namespace sf
{
	class RenderWindow;
	class Event;
}

class UiManager
{
private:

	ultralight::RefPtr<ultralight::Renderer> mRenderer;
	ultralight::RefPtr<ultralight::View> mView;

	UiManager();
	UiManager(const UiManager& other) = delete;	

	static UiManager* mInstance;

public:
	void Draw(sf::RenderWindow& window);
	void ProcessEvents(sf::Event sfEvent);
	void Update();


	static UiManager& GetInstance();
	void Shutdown();
};