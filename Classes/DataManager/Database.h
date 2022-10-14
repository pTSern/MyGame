#pragma once
#include "sqLite3/sqlite3.h"
#include "cocos2d.h"

#define FALSE 0
#define TRUE 1

class Database
{
public:
	inline static Database* GetInstance()
	{
		return sp_pInstance = (sp_pInstance != nullptr) ? sp_pInstance : new Database();
	}
	inline sqlite3* GetDatabase()
	{
		return this->p_pDatabase;
	}
	inline sqlite3_stmt* GetStatement()
	{
		return this->p_pStatement;
	}
	inline sqlite3_stmt** GetPStatement()
	{
		return &this->p_pStatement;
	}
	inline bool GetPrepareV2(std::string command, const char **pzTail = 0)
	{
		int result = sqlite3_prepare_v2(this->p_pDatabase, command.c_str(), -1, &this->p_pStatement, pzTail);
		cocos2d::log(command.c_str());
		cocos2d::log(("DATABASE: Get prepare v2 result: " + std::to_string(result)).c_str());
		if ( result == SQLITE_OK)
		{
			return true;
		}
		return false;
	}
	inline bool GetExec(std::string command)
	{
		int result = sqlite3_exec(this->p_pDatabase, command.c_str(), NULL, NULL, NULL);
		cocos2d::log( ("DATABASE: Get exec result: " + std::to_string(result)).c_str());
		cocos2d::log(command.c_str());
		if (result == SQLITE_OK)
		{
			return true;
		}
		return false;
	}
public:
	bool OpenConnection();
	bool CloseConnection();
	void SupperInit();
private:
	void CreateDatabase();
private:
	static Database *sp_pInstance;
	std::string p_sPath;

	sqlite3 *p_pDatabase;
	sqlite3_stmt *p_pStatement;
private:
	Database();
};
