#include "LocalizationManager.h"

LocalizationManager *LocalizationManager::mInstance = nullptr;

namespace SQLOperations
{
	namespace Query
	{
		const char* kLOC_TABLE = "loc";
		const char* kLOC_KEY = "loc_key";
		const char* kLOC_VALUE = "loc_value_";

		const int kREAD_FULL_QUERY = -1;
		const char** kNO_TAIL = nullptr;

		const int kLEFTMOST_COLUMN = 0;
	}
}

LocalizationManager::LocalizationManager()
{
	OpenDatabase(LocalizationManager::kLOC_DB);
};

LocalizationManager* LocalizationManager::GetInstance()
{
	if (mInstance == nullptr)
	{
		mInstance = new LocalizationManager();
	}

	return mInstance;
}

void LocalizationManager::Shutdown()
{
	sqlite3_close(mInstance->mLocalizationDatabase);
	delete mInstance;
}

bool LocalizationManager::OpenDatabase(const char* databaseName)
{
	int rc = 0;

	rc = sqlite3_open(databaseName, &mLocalizationDatabase);

	if (rc)
	{
		sqlite3_close(mLocalizationDatabase);

		return false;
	}

	return true;
}

std::unique_ptr<std::string> LocalizationManager::GetLocByKey(const std::string& key)
{
	if (LocalizeData)
	{
		char lang[16];
		sprintf_s(lang, 16, "%s%s", SQLOperations::Query::kLOC_VALUE, mLanguage);

		char query[128];
		sprintf_s(query, 128, "SELECT %s FROM %s WHERE %s==\"%s\"", lang, SQLOperations::Query::kLOC_TABLE, SQLOperations::Query::kLOC_KEY, key.c_str());

		sqlite3_stmt* stmt;
		int err;

		err = sqlite3_prepare_v2(mLocalizationDatabase, query, SQLOperations::Query::kREAD_FULL_QUERY, &stmt, SQLOperations::Query::kNO_TAIL);

		if (err == SQLITE_OK)
		{
			err = sqlite3_step(stmt);

			if (err != SQLITE_ERROR)
			{
				const char* LocValue = (const char*)sqlite3_column_text(stmt, SQLOperations::Query::kLEFTMOST_COLUMN);

				if (LocValue == NULL)
				{
					LocValue = key.c_str();
				}

				return std::make_unique<std::string>(LocValue);
			}
		}

		char errMessage[128];
		sprintf_s(errMessage, 128, "Error in retrieving loc key: %s", key.c_str());
		std::cout << errMessage << std::endl;
	}

	return std::make_unique<std::string>(key);
}