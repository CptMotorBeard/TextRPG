#pragma once
#include "BaseIncludes.h"
#include <Ultralight/Ultralight.h>

namespace sf
{
	class RenderWindow;
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

	void Update();


	static UiManager& GetInstance();
	void Shutdown();
};