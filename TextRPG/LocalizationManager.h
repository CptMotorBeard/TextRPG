#pragma once
#include "sqlite3.h"

class LocalizationManager
{
public:
	const char* kLOC_DB = "loc.db";

	LocalizationManager();
	~LocalizationManager();
	std::unique_ptr<std::string> GetLocByKey(const std::string& key);

	static LocalizationManager* GetInstance();
	static void Shutdown();

private:
	sqlite3* mLocalizationDatabase;
	static LocalizationManager *mInstance;

	bool OpenDatabase(const char* databaseName);
};