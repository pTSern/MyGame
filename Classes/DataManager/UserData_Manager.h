#pragma once
#include "Database.h"
#include "Extention/UserExtend.h"
#include "ChampionData_Manager.h"

enum class ItemType
{
	ITEM = 0,
	WEAPON = 1
};


struct UserOwnedItem
{
public:
	int g_nItemId, g_nAmount;
	ItemType g_eType;
};

class UserDataManager
{
public:
	inline static UserDataManager* GetInstance()
	{
		return sp_pInstance = (sp_pInstance != nullptr) ? sp_pInstance : new UserDataManager();
	}
public:
	UserInformations* LoadUserInformationByUsernameNPass(std::string sUsername, std::string sPassword);
	UserGameDetails* LoadUserGameDetailsById(int nId);
	EconomyUnit* LoadUserEconomyById(int nId);
	UserUITexture* LoadUserUITextureById(int nId);
	UserSound* LoadUserSound(int nId);
	int LoadSelectedChampionId(int nId);
	Champion* ReloadSelectedChampion(int userId, int cId);

	bool CheckLogin(std::string sFirstInput, std::string sPassword);
	std::map<int, UserOwnedItem*> LoadUserInventoryById(int nId);
	std::map<int, Champion*> LoadOwnedChampionList(int nId);

	void UpdateUserGameDetails(int nUserId, UserGameDetails* newUGD);
	void UpdateUserEconomy(int nUserId, EconomyUnit* newUGD);
	void UpdateSelectedChampionId(int nUserId, int newSelectId);
	void UpdatePassword(int nUserId, std::string s);
	void UpdateChampionEXP(int nUserId, int nChampionId, float exp);
	void UpdateUserSoundVolume(int nUserId, float fVolume);
	//void UpdateUserInformation();
private:
	static UserDataManager* sp_pInstance;
	//User* p_pUserData;
private:
	UserDataManager();
};