#pragma once
#include "Inventory/Inventory.h"
#include "DataManager/UserData_Manager.h"
#include "DataManager/ItemData_Manager.h"
#include "DataManager/ChampionData_Manager.h"
#include "Extention/UserExtend.h"

class User
{
public:
	inline static User* GetInstance()
	{
		return sp_pInstance = (sp_pInstance != nullptr) ? sp_pInstance : new User();
	}

	Champion* GetOwnedChampion_byID(int id);

	inline int GetUserId()
	{
		return p_pUserInformations->g_nID;
	}

	inline void SetUserInformation(UserInformations* pUserInformations)
	{
		this->p_pUserInformations = pUserInformations;
	}
	inline void SetUserGameDetail(UserGameDetails* pUserGameDetails)
	{
		this->p_pUserGameDetails = pUserGameDetails;
	}

	inline EconomyUnit* GetUserEconomy()
	{
		return this->p_pEco;
	}
	inline UserInformations* GetUserInformation()
	{
		return this->p_pUserInformations;
	}
	inline UserUITexture* GetUserUITexture()
	{
		return this->p_pUserUITexture;
	}
	inline UserSound* GetUserSound()
	{
		return this->p_pUserSound;
	}
	inline float GetUserWinRateIPC()
	{
		return this->p_pUserGameDetails->GetWinrate();
	}
	inline float GetUserWinRate()
	{
		return this->p_pUserGameDetails->GetWinrate() / 100;
	}
	inline UserGameDetails* GetUserGameDetail()
	{
		return this->p_pUserGameDetails;
	}
	inline Inventory* GetUserInventory()
	{
		return this->p_pUserInventory;
	}
	inline Champion* GetSelectedChampion()
	{
		return this->p_mOwnedChampionsList[p_nSelectedChampionId];
	}
	inline std::map<int, Champion*> GetOwnedChampionList()
	{
		return this->p_mOwnedChampionsList;
	}
	inline void SetSelectedChampionId(int nId)
	{
		this->p_nSelectedChampionId = nId;
	}
	inline void ReLoadSelectedChampionId()
	{
		this->p_mOwnedChampionsList[p_nSelectedChampionId] = UserDataManager::GetInstance()->ReloadSelectedChampion(p_pUserInformations->g_nID, p_nSelectedChampionId);
		this->p_mOwnedChampionsList[p_nSelectedChampionId]->Init();
	}
public:
	void SupperInit(std::string username, std::string password);
	void UpdatePass(std::string s);

	void LoadOwnedWeapon();
	void LoadOwnedChampion();
	void LoadEconomy();
	void LoadUserGameDetails();
	void LoadUserInventory();
	void LoadUserInformation(std::string username, std::string password);
	void LoadUserUITexture();
	void LoadSelectedChampionId();
	void LoadSelectedChampion();
	void LoadUserSound();

	void WinGame();
	void OnEnterBattle();
	void OnExitBattle(bool isWin);
	void log();
private:
	User() {}

	static User* sp_pInstance;
	std::map<int, Champion*> p_mOwnedChampionsList;
	std::map<int, Item*> p_mOwnedItemsList;
	std::map<int, Weapon*> p_mOwnedWeaponsList;

	EconomyUnit* p_pEco;
	UserInformations* p_pUserInformations;
	UserGameDetails* p_pUserGameDetails;
	Inventory* p_pUserInventory = new Inventory();
	UserUITexture* p_pUserUITexture;
	UserSound* p_pUserSound;

	int p_nSelectedChampionID;
	int p_nMaxItemsSlot;
	int p_nSelectedChampionId;
};

