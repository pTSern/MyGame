#include "LogManager.h"
#include <fstream>

LogManager* LogManager::p_pInstance = nullptr;

LogManager::LogManager()
{
    time_t time = std::time(nullptr);
    tm* timeinfo = localtime(&time);

    //file_name index
    int nNum = 1;
    //Get Current year/month/day
    p_sCurrentTime =std::to_string(timeinfo->tm_year + 1900) + "-" + std::to_string(timeinfo->tm_mon + 1) + "-" + std::to_string(timeinfo->tm_mday);

    //Create file_name = current_time-number.log
    p_sLogName = p_sCurrentTime + "-" + std::to_string(nNum) + ".log";

    //Get root path = Root/
    p_sRootPath = cocos2d::FileUtils::getInstance()->getDefaultResourceRootPath() + "Log";

    //Create folder: Root/Log
    mkdir(p_sRootPath.c_str());

    //Create path = Root/Log/file_name
    p_sPath = p_sRootPath + "/" + p_sLogName;
    
    //Loop check valid path
    if (CheckValidPathLog(nNum)) {}
}

void LogManager::Log(std::string sLog)
{
    time_t time = std::time(nullptr);
    tm* timeinfo = localtime(&time);
    std::ofstream as(p_sPath);
    std::string  sCurrentTime = "[" + std::to_string(timeinfo->tm_hour) + ":" + std::to_string(timeinfo->tm_min) + ":" + std::to_string(timeinfo->tm_sec) + "] ";

    as << (sCurrentTime + sLog);
    as.close();

    //cocos2d::FileUtils::getInstance()->writeStringToFile(sCurrentTime + sLog, p_sPath);
    
}

bool LogManager::CheckValidPathLog(int n)
{
    if (cocos2d::FileUtils::getInstance()->isFileExist(p_sPath))
    {
        p_sLogName = p_sCurrentTime + "-" + std::to_string(n + 1) + ".log";
        p_sPath = p_sRootPath + "/" + p_sLogName;
        return this->CheckValidPathLog(n + 1);
    }
    else return true;
}