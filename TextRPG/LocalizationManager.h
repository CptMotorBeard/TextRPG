#pragma once
#include "BaseIncludes.h"
#include "sqlite3.h"

class LocalizationManager
{
public:
	const char* kLOC_DB = "loc.db";
	bool LocalizeData = true;	

	LocalizationManager();
	std::unique_ptr<std::string> GetLocByKey(const std::string& key);

	static LocalizationManager* GetInstance();
	static void Shutdown();

private:
	char mLanguage[3] = "en";

	sqlite3* mLocalizationDatabase;
	static LocalizationManager *mInstance;

	bool OpenDatabase(const char* databaseName);
};