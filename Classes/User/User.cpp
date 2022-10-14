#include "User.h"
User* User::sp_pInstance = nullptr;

Champion* User::GetOwnedChampion_byID(int id)
{
	for (int i = 0; i < p_mOwnedChampionsList.size(); i++)
	{
		if (p_mOwnedChampionsList[i]->GetChampionStatics()->g_nChampionID == id)
		{
			cocos2d::log("USER: Finish get owned champion id");
			return p_mOwnedChampionsList[i];
		}
	}
	cocos2d::log("USER: There no owned champion or something wrong here");
}

void User::LoadOwnedWeapon()
{
}

void User::LoadOwnedChampion()
{
	this->p_mOwnedChampionsList = UserDataManager::GetInstance()->LoadOwnedChampionList(this->p_pUserInformations->g_nID);
	cocos2d::log("USER: Finish load owned champion list");
	for (auto& x : p_mOwnedChampionsList)
	{
		x.second->Init();
	}
	cocos2d::log("USER: Finish Init owned champion in list");
}
void User::LoadEconomy()
{
	this->p_pEco = UserDataManager::GetInstance()->LoadUserEconomyById(this->p_pUserInformations->g_nID);
	cocos2d::log("USER: Finish load user economy");

}
void User::LoadUserGameDetails()
{
	this->p_pUserGameDetails = UserDataManager::GetInstance()->LoadUserGameDetailsById(this->p_pUserInformations->g_nID);
	cocos2d::log("USER: Finish load user detail");
}
void User::LoadUserInformation(std::string username, std::string password)
{
	this->p_pUserInformations = UserDataManager::GetInstance()->LoadUserInformationByUsernameNPass(username, password);
	cocos2d::log("USER: Finish load user information");
}
void User::LoadUserUITexture()
{
	this->p_pUserUITexture = UserDataManager::GetInstance()->LoadUserUITextureById(this->p_pUserInformations->g_nID);
	cocos2d::log("USER: Finish load user ui texture");
}
void User::LoadSelectedChampionId()
{
	this->p_nSelectedChampionId = UserDataManager::GetInstance()->LoadSelectedChampionId(this->p_pUserInformations->g_nID);
	cocos2d::log("USER: Finish load selected champion id");
}
void User::LoadSelectedChampion()
{
	this->p_mOwnedChampionsList[p_nSelectedChampionId] = UserDataManager::GetInstance()->ReloadSelectedChampion(this->p_pUserInformations->g_nID, this->p_nSelectedChampionId);
}
void User::LoadUserSound()
{
	this->p_pUserSound = UserDataManager::GetInstance()->LoadUserSound(this->p_pUserInformations->g_nID);
	cocos2d::log("USER: Finish load user audio");
}
void User::LoadUserInventory()
{
	int index = 0;
	auto f = UserDataManager::GetInstance()->LoadUserInventoryById(this->p_pUserInformations->g_nID);
	if (f.size() > 0)
	{
		for (auto& x : f)
		{
			p_pUserInventory->g_mInven[index] = new ItemInInventory();

			p_pUserInventory->g_mInven[index]->g_nAmount = x.second->g_nAmount;

			switch (x.second->g_eType)
			{
			case ItemType::ITEM:
				p_pUserInventory->g_mInven[index]->g_pItem = ItemDataManager::GetInstance()->GetItemById(x.second->g_nItemId);
				break;
			case ItemType::WEAPON:
				p_pUserInventory->g_mInven[index]->g_pItem = ItemDataManager::GetInstance()->GetWeaponById(x.second->g_nItemId);
				break;
			}

			index++;
			cocos2d::log("USER: Finish load 1 item in inventory");
		}
	}
	else cocos2d::log("USER: There no item in inventory or smt wrong here");
}
void User::SupperInit(std::string username, std::string password)
{
	this->LoadUserInformation(username, password);
	this->LoadUserUITexture();
	this->LoadUserGameDetails();
	this->LoadEconomy();
	this->LoadUserSound();
	this->LoadUserInventory();
	this->LoadSelectedChampionId();
	this->LoadOwnedChampion();
}

void User::UpdatePass(std::string s)
{
	UserDataManager::GetInstance()->UpdatePassword(p_pUserInformations->g_nID,s);
}
void User::log()
{
	cocos2d::log("L1111111111111111");
	cocos2d::log(std::to_string( p_pUserInformations->g_nID).c_str());
	cocos2d::log("L22222222222222222");
	cocos2d::log(std::to_string(p_pUserGameDetails->g_fWinrate).c_str());
	cocos2d::log("L33333333333333");
	cocos2d::log(std::to_string(p_pEco->g_fSp).c_str());
	cocos2d::log("L144444444444444444444");
	cocos2d::log(std::to_string(p_nSelectedChampionId).c_str());
	cocos2d::log("L5555555555555555");
	cocos2d::log((std::to_string((int)p_mOwnedChampionsList[0]->GetChampionStatics()->g_mainATT)).c_str());
	cocos2d::log("L6666666666666666666");
	cocos2d::log((p_pUserInventory->g_mInven[0]->g_pItem->GetSText()).c_str());
	cocos2d::log("L77777777777777777");

}

void User::OnEnterBattle()
{
	//Clone user game data
	auto pGameDataClone = UserGameDetails::Clone(this->p_pUserGameDetails);
	auto pEconomyClone = EconomyUnit::Clone(this->p_pEco);

	pGameDataClone->g_nLoseGames++;
	if (pEconomyClone->g_fXu > 0) pEconomyClone->g_fXu -= 10 + this->p_mOwnedChampionsList[p_nSelectedChampionId]->GetChampionStatics()->g_nLevel * 10;
	pEconomyClone->AutoValidMoney();

	//Database::GetInstance()->CloseConnection();
	UserDataManager::GetInstance()->UpdateUserGameDetails(p_pUserInformations->g_nID, pGameDataClone);
	UserDataManager::GetInstance()->UpdateUserEconomy(p_pUserInformations->g_nID, pEconomyClone);

}
void User::WinGame()
{
	this->p_pUserGameDetails->g_nWinGames++;
	this->p_pEco->g_fXu += 10;
	this->p_mOwnedChampionsList[p_nSelectedChampionId]->AddChampionEXP(10);

	UserDataManager::GetInstance()->UpdateUserGameDetails(p_pUserInformations->g_nID, this->p_pUserGameDetails);
	UserDataManager::GetInstance()->UpdateUserEconomy(p_pUserInformations->g_nID, this->p_pEco);
	UserDataManager::GetInstance()->UpdateChampionEXP(p_pUserInformations->g_nID, this->p_nSelectedChampionId, this->p_mOwnedChampionsList[p_nSelectedChampionId]->GetChampionEXP());
}
void User::OnExitBattle(bool isWin)
{
	cocos2d::log("++++++++++++++++++++++++++++++++++++++++++++++++");
	if (isWin) User::WinGame();

	//Reload some data
	this->LoadUserGameDetails();
	this->LoadEconomy();
	this->LoadSelectedChampion();

	cocos2d::log("++++++++++++++++++++++++++++++++++++++++++++++++");
}