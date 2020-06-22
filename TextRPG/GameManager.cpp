#include <fstream>
#include "GameManager.h"

GameManager& GameManager::GetInstance()
{
	static GameManager* mInstance = nullptr;
	if (mInstance == nullptr)
	{
		mInstance = new GameManager();

		mInstance->mGlobalFont = new sf::Font();
		mInstance->mGlobalFont->loadFromFile("Resources/Roboto Font/Roboto-Regular.ttf");
	}

	return *mInstance;
}

void GameManager::Shutdown()
{
	delete mGlobalFont;
	delete this;
}

GameManager::GameManager()
{
	mGlobalFont = nullptr;
}

sf::Font* GameManager::GetGlobalFont()
{
	return mGlobalFont;
}

void GameManager::SaveGame(uint8 fileNumber)
{
	const std::string filename = "Resources/Saves/File" + std::to_string(fileNumber);
	const uint8 charXorCipher = 0xB6;

	json data = GameWorld.SerializeData();
	std::string ostring = data.dump();
	
	std::ofstream ofile(filename);
	if (ofile.good())
	{
		for (char& c : ostring)
		{
			c ^= charXorCipher;
		}

		ofile << ostring;
	}
	ofile.close();
}

void GameManager::LoadGame(uint8 fileNumber)
{
	const std::string filename = "Resources/Saves/File" + std::to_string(fileNumber);
	const uint8 charXorCipher = 0xB6;

	std::ifstream ifile(filename);
	if (ifile.good())
	{
		std::string istring;
		ifile >> istring;

		for (char& c : istring)
		{
			c ^= charXorCipher;
		}

		json data = json::parse(istring.c_str());
		GameWorld.DeserializeData(data);
	}
	ifile.close();
}