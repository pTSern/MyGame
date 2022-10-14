#pragma once
#include "ObjectManager/LogManager.h"
#include <string>
struct EconomyUnit 
{
public:
	static EconomyUnit* Clone(EconomyUnit* p)
	{
		EconomyUnit* pClone = new (std::nothrow) EconomyUnit();

		pClone->g_fXu = p->g_fXu;
		pClone->g_fSp = p->g_fSp;

		return pClone;
	}
public:
	float g_fXu, g_fSp;
	void AutoValidMoney()
	{
		if (g_fXu < 0) g_fXu = 0;
		if (g_fSp < 0) g_fSp = 0;
	}
};

struct UserInformations
{
public:
	std::string g_sNickname;
	std::string g_sUsername, g_sPassword;
	int g_nID;
};
struct UserUITexture
{
public:
	std::string g_sForceBar; 
	std::string g_sBackground;
	std::string g_sHPBar;
	std::string g_sSTMBar;
	std::string g_sAvatar;
	std::string g_sFrame;
};
struct UserSound
{
public:
	std::string g_sGameFight;
	std::string g_sMenu;
	float g_fVolume;
};
struct UserGameDetails
{
public:
	static UserGameDetails* Clone(UserGameDetails* p)
	{
		UserGameDetails* pClone = new (std::nothrow) UserGameDetails();

		pClone->g_nWinGames = p->g_nWinGames;
		pClone->g_nLoseGames = p->g_nLoseGames;

		return pClone;
	}
public:
	float g_fWinrate;
	int g_nWinGames, g_nLoseGames;
public:
	void CalculateWinRate()
	{
		if ((g_nLoseGames + g_nWinGames) == 0) g_fWinrate = 0;
		else g_fWinrate = (((float)g_nWinGames / ((float)g_nWinGames + (float)g_nLoseGames)) * 100);
		cocos2d::log(("USER WIN RATE: " + std::to_string(g_fWinrate)).c_str());
	}
	float GetWinrate()
	{
		CalculateWinRate();
		return this->g_fWinrate;
	}
};

