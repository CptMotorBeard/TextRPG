#pragma once
#include "BaseIncludes.h"
#include "sqlite3.h"

struct LocalizationKey
{
public:
	struct ENTRY
	{
	public:
		const static char* TITLE;
	};
};

class LocalizationManager
{
public:
	const char* kLOC_DB = "Resources/loc.db";
	bool LocalizeData = true;	

	LocalizationManager();
	LocalizationManager(const LocalizationManager& other) = delete;

	std::unique_ptr<std::string> GetLocByKey(const std::string& key);

	static LocalizationManager& GetInstance();
	void Shutdown();

private:
	char mLanguage[3] = "en";

	sqlite3* mLocalizationDatabase;

	bool OpenDatabase(const char* databaseName);
};