#pragma once
#include "cocos2d.h"
#include <direct.h>
class LogManager
{
public:
	static LogManager* GetInstance()
	{
		return p_pInstance = (p_pInstance != nullptr) ? p_pInstance : new LogManager();
	}
	void Log(std::string sLog);
	bool CheckValidPathLog(int n);
private:
	LogManager();
	std::string p_sPath, p_sCurrentTime, p_sLogName, p_sRootPath;
	static LogManager* p_pInstance;
};
