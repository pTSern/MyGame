#include "Database.h"

Database* Database::sp_pInstance = nullptr;

Database::Database()
{
	this->p_sPath = cocos2d::FileUtils::getInstance()->getWritablePath() + "database.db";
	this->OpenConnection();
	cocos2d::log(("DATABASE LOCATE:  " + p_sPath).c_str());
}
bool Database::OpenConnection()
{
	if (sqlite3_open(this->p_sPath.c_str(), &this->p_pDatabase) == SQLITE_OK)
	{
		cocos2d::log("DATABASE: Open connection successfully");
		return true;
	}
	cocos2d::log("DATABASE: CANNOT open connection");
	this->CloseConnection();
	return false;
}

bool Database::CloseConnection()
{
	sqlite3_close(this->p_pDatabase);
	return true;
}
void Database::CreateDatabase()
{

}
void Database::SupperInit()
{

}