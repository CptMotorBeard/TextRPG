#include "UiManager.h"

#include <AppCore/Platform.h>
#include "SFML/Graphics.hpp"

UiManager::UiManager()
{
	ultralight::Config config;

	config.resource_path = "Resources/UI/";
	config.use_gpu_renderer = false;
	config.device_scale = 1.0;

	ultralight::Platform &platformInstance = ultralight::Platform::instance();

	platformInstance.set_config(config);
	platformInstance.set_font_loader(ultralight::GetPlatformFontLoader());
	platformInstance.set_file_system(ultralight::GetPlatformFileSystem("."));
	platformInstance.set_logger(ultralight::GetDefaultLogger("ultralight.log"));

	mRenderer = ultralight::Renderer::Create();

	mView = mRenderer->CreateView(500, 500, false, nullptr);
	mView->LoadHTML("<h1>Hello World!</h1>");
	mView->Focus();
}

void UiManager::Update()
{
	mRenderer->Update();
	mRenderer->Render();
}

void UiManager::Draw(sf::RenderWindow& window)
{
	ultralight::Surface* surf = mView->surface();
	ultralight::BitmapSurface* bitmap_surface = (ultralight::BitmapSurface*)surf;
	ultralight::RefPtr<ultralight::Bitmap> bitmap = bitmap_surface->bitmap();

	uint8* pixels = (uint8 *)bitmap->LockPixels();
	size_t size = bitmap->size();

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