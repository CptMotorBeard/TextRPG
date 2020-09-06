#include "UiManager.h"

#include <AppCore/Platform.h>
#include "SFML/Graphics.hpp"
#include "SFML-manager.h"

UiManager::UiManager()
{
	ultralight::Config config;

	config.resource_path = "Resources/UI";
	config.use_gpu_renderer = false;
	config.device_scale = 1.0;

	ultralight::Platform &platformInstance = ultralight::Platform::instance();

	platformInstance.set_config(config);
	platformInstance.set_font_loader(ultralight::GetPlatformFontLoader());
	platformInstance.set_file_system(ultralight::GetPlatformFileSystem("Resources/UI"));
	platformInstance.set_logger(ultralight::GetDefaultLogger("ultralight.log"));

	mRenderer = ultralight::Renderer::Create();

	mView = mRenderer->CreateView(500, 500, false, nullptr);
	mView->LoadURL("file:///test.html");
	mView->Focus();
}

void UiManager::Update()
{
	mRenderer->Update();
}

void UiManager::ProcessEvents(sf::Event sfEvent)
{
	bool didLeftClick = sfEvent.mouseButton.button == sf::Mouse::Button::Left;
	bool didRightClick = sfEvent.mouseButton.button == sf::Mouse::Button::Right;
	bool didScrollClick = sfEvent.mouseButton.button == sf::Mouse::Button::Middle;

	if (sfEvent.type == sf::Event::MouseButtonPressed || sfEvent.type == sf::Event::MouseButtonReleased)
	{
		ultralight::MouseEvent evt;

		if (sfEvent.type == sf::Event::MouseButtonPressed)
			evt.type = ultralight::MouseEvent::kType_MouseDown;
		else
			evt.type = ultralight::MouseEvent::kType_MouseUp;

		if (didLeftClick)
			evt.button = ultralight::MouseEvent::Button::kButton_Left;
		else if (didRightClick)
			evt.button = ultralight::MouseEvent::Button::kButton_Right;
		else if (didScrollClick)
			evt.button = ultralight::MouseEvent::Button::kButton_Middle;

		evt.x = sfEvent.mouseButton.x;
		evt.y = sfEvent.mouseButton.y;

		mView->FireMouseEvent(evt);
	}
	else if (sfEvent.type == sf::Event::MouseMoved)
	{
		ultralight::MouseEvent evt;
		evt.type = ultralight::MouseEvent::kType_MouseMoved;

		evt.x = sfEvent.mouseMove.x;
		evt.y = sfEvent.mouseMove.y;

		mView->FireMouseEvent(evt);
	}	
}

void UiManager::Draw(sf::RenderWindow& window)
{
	if (SFML_Manager::GetInstance().WindowWasResized)
	{
		sf::Vector2u windowSize = window.getSize();
		mView->Resize(windowSize.x, windowSize.y);
	}	

	mRenderer->Render();

	ultralight::Surface* surf = mView->surface();
	ultralight::BitmapSurface* bitmap_surface = (ultralight::BitmapSurface*)surf;
	ultralight::RefPtr<ultralight::Bitmap> bitmap = bitmap_surface->bitmap();

	uint8* pixels = (uint8 *)bitmap->LockPixels();

	size_t width = bitmap->width();
	size_t height = bitmap->height();

	sf::Texture tex;
	tex.create(width, height);
	tex.update(pixels);

	sf::Sprite sp;
	sp.setTexture(tex);
	sp.setPosition(0, 0);

	window.draw(sp);
	bitmap->UnlockPixels();
}

UiManager& UiManager::GetInstance()
{
	UiManager* mInstance = nullptr;
	if (mInstance == nullptr)
	{
		mInstance = new UiManager();
	}

	return *mInstance;
}

void UiManager::Shutdown()
{
	delete this;
}