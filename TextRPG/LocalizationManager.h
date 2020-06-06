#pragma once
#include "BaseIncludes.h"
#include "sqlite3.h"

namespace LocalizationKey
{
	namespace ENTRY
	{
		const char* TITLE = "ENTRY_TITLE";
	}
}

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