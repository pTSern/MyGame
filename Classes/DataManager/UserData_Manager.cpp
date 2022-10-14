#include "UserData_Manager.h"
UserDataManager* UserDataManager::sp_pInstance = nullptr;

UserDataManager::UserDataManager()
{
	
}

UserInformations* UserDataManager::LoadUserInformationByUsernameNPass(std::string sUsername, std::string sPassword)
{
	std::string command = "SELECT * FROM user_informations WHERE username = '" + sUsername + "' AND password = '" + sPassword + "' ";
		
	if (Database::GetInstance()->GetPrepareV2(command))
	{
		int result = sqlite3_step(Database::GetInstance()->GetStatement());

		if (result == SQLITE_ROW)
		{
			UserInformations* pInf = new UserInformations();
			pInf->g_sUsername = sUsername;
			pInf->g_sPassword = "";
			pInf->g_nID = sqlite3_column_int(Database::GetInstance()->GetStatement(), 0);
			pInf->g_sNickname = std::string(reinterpret_cast<const char*>(sqlite3_column_text(Database::GetInstance()->GetStatement(), 1)));
			Database::GetInstance()->CloseConnection();
			LogManager::GetInstance()->Log("USER DATA MANAGER: Load user information by username and password successfully");
			return pInf;
		}
			
	}
	return nullptr;
}
UserSound* UserDataManager::LoadUserSound(int nId)
{
	std::string command = "SELECT * FROM user_audio WHERE userId = " + std::to_string(nId);
	if (Database::GetInstance()->GetPrepareV2(command))
	{
		int result = sqlite3_step(Database::GetInstance()->GetStatement());
		if (result == SQLITE_ROW)
		{
			UserSound* pInf = new UserSound();
			pInf->g_sMenu = std::string(reinterpret_cast<const char*>(sqlite3_column_text(Database::GetInstance()->GetStatement(), 1)));
			pInf->g_sGameFight = std::string(reinterpret_cast<const char*>(sqlite3_column_text(Database::GetInstance()->GetStatement(), 2)));
			pInf->g_fVolume = sqlite3_column_double(Database::GetInstance()->GetStatement(), 3);
			LogManager::GetInstance()->Log("USER DATA MANAGER: Load user audio successfully");
			return pInf;
		}
	}
	return nullptr;
}
UserUITexture* UserDataManager::LoadUserUITextureById(int nId)
{
	std::string command = "SELECT * FROM user_ui_texture WHERE userId = " + std::to_string(nId);
	if (Database::GetInstance()->GetPrepareV2(command))
	{
		int result = sqlite3_step(Database::GetInstance()->GetStatement());

		if (result == SQLITE_ROW)
		{
			UserUITexture* pUT = new UserUITexture();
			pUT->g_sForceBar = std::string(reinterpret_cast<const char*>(sqlite3_column_text(Database::GetInstance()->GetStatement(), 1)));
			pUT->g_sBackground = std::string(reinterpret_cast<const char*>(sqlite3_column_text(Database::GetInstance()->GetStatement(), 2)));
			pUT->g_sHPBar = std::string(reinterpret_cast<const char*>(sqlite3_column_text(Database::GetInstance()->GetStatement(), 3)));
			pUT->g_sSTMBar = std::string(reinterpret_cast<const char*>(sqlite3_column_text(Database::GetInstance()->GetStatement(), 4)));
			pUT->g_sAvatar = std::string(reinterpret_cast<const char*>(sqlite3_column_text(Database::GetInstance()->GetStatement(), 5)));
			pUT->g_sFrame = std::string(reinterpret_cast<const char*>(sqlite3_column_text(Database::GetInstance()->GetStatement(), 6)));
			LogManager::GetInstance()->Log("USER DATA MANAGER: Load user game details by id successfully");
			return pUT;
		}

	}
	return nullptr;
}
UserGameDetails* UserDataManager::LoadUserGameDetailsById(int nId)
{
	std::string command = "SELECT * FROM user_game_data WHERE userId = " + std::to_string(nId);

	if (Database::GetInstance()->GetPrepareV2(command))
	{
		int result = sqlite3_step(Database::GetInstance()->GetStatement());

		if (result == SQLITE_ROW)
		{
			UserGameDetails* pUGD = new UserGameDetails();
			pUGD->g_nWinGames = sqlite3_column_int(Database::GetInstance()->GetStatement(), 1);
			pUGD->g_nLoseGames = sqlite3_column_int(Database::GetInstance()->GetStatement(), 2);
			pUGD->CalculateWinRate();
			LogManager::GetInstance()->Log("USER DATA MANAGER: Load user game details by id successfully");
			return pUGD;
		}

	}
	return nullptr;
}

int UserDataManager::LoadSelectedChampionId(int nId)
{
	int id = -1;
	std::string command = "SELECT selectedId FROM user_game_data WHERE userId = " + std::to_string(nId);

	if (Database::GetInstance()->GetPrepareV2(command))
	{
		int result = sqlite3_step(Database::GetInstance()->GetStatement());

		if (result == SQLITE_ROW)
		{
			id = sqlite3_column_int(Database::GetInstance()->GetStatement(), 0);
			LogManager::GetInstance()->Log("USER DATA MANAGER: Load user's selected champion's id successfully");
			return id;
		}

	}
	return id;
}

bool UserDataManager::CheckLogin(std::string sFirstInput, std::string sPassword)
{
	bool b = false;
	std::string command = "SELECT userId FROM user_informations WHERE username = '" + sFirstInput + "' AND password = '" + sPassword + "' ";
	std::string extendcmd = "OR email = '" + sFirstInput + "' AND password = '" + sPassword + "' ";
	if (Database::GetInstance()->GetPrepareV2(command + extendcmd))
	{
		int result = sqlite3_step(Database::GetInstance()->GetStatement());
		cocos2d::log(("USER DATA MANAGER: CHECKLOGIN RESULT " + std::to_string(result)).c_str());
		if (result == SQLITE_ROW)
		{
			b = true;
			LogManager::GetInstance()->Log("USER DATA MANAGER: Check login successfully");
		}
	}
	return b;
}

std::map<int, UserOwnedItem*> UserDataManager::LoadUserInventoryById(int nId)
{
	std::map<int, UserOwnedItem*> uMap;
	std::string command = "SELECT user_inventory.itemId, user_inventory.amount, item.item_type_Id FROM user_inventory INNER JOIN item ON user_inventory.itemId = item.itemId";
	std::string extendcmd = " WHERE user_inventory.userId = " + std::to_string(nId);
		
	if (Database::GetInstance()->GetPrepareV2(command + extendcmd))
	{
		int result;
		while (true)
		{
			result = sqlite3_step(Database::GetInstance()->GetStatement());

			if (result == SQLITE_ROW)
			{
				UserOwnedItem* pu = new UserOwnedItem();
				pu->g_nItemId = sqlite3_column_int(Database::GetInstance()->GetStatement(), 0);
				pu->g_nAmount = sqlite3_column_int(Database::GetInstance()->GetStatement(), 1);
				pu->g_eType = (ItemType)sqlite3_column_int(Database::GetInstance()->GetStatement(), 2);
				uMap[pu->g_nItemId] = pu;
				LogManager::GetInstance()->Log("USER DATA MANAGER: Load user's inventory by user's id successfully");
			}
			else break;
		}
	}
	return uMap;
}

EconomyUnit* UserDataManager::LoadUserEconomyById(int nId)
{
	std::string command = "SELECT * FROM user_economy WHERE userId = " + std::to_string(nId);
	if (Database::GetInstance()->GetPrepareV2(command))
	{
		int result = sqlite3_step(Database::GetInstance()->GetStatement());

		if (result == SQLITE_ROW)
		{
			EconomyUnit* pE = new EconomyUnit();
			pE->g_fXu = sqlite3_column_double(Database::GetInstance()->GetStatement(), 1);
			pE->g_fSp = sqlite3_column_double(Database::GetInstance()->GetStatement(), 2);
			Database::GetInstance()->CloseConnection();
			LogManager::GetInstance()->Log("USER DATA MANAGER: Load user's economy by user's id successfully");
			return pE;
		}
	}
	return nullptr;
}

std::map<int, Champion*> UserDataManager::LoadOwnedChampionList(int nId)
{
	std::vector<int> championIdList;
	std::map<int, Champion*> championList;
	std::string command = "SELECT * FROM user_owned_champion WHERE userId = " + std::to_string(nId);
	if (Database::GetInstance()->GetPrepareV2(command))
	{
		int result = 0;
		while (true)
		{
			result = sqlite3_step(Database::GetInstance()->GetStatement());

			if (result == SQLITE_ROW)
			{
				championIdList.push_back(sqlite3_column_int(Database::GetInstance()->GetStatement(), 1));
				LogManager::GetInstance()->Log("USER DATA MANAGER: Load user's owned champion list by user's id successfully");
			}
			else break;
		}
			
	}
	for (auto& x : championIdList)
	{
		//cocos2d::log(("USER DATA MANAGER: CHAMPION ID: " + std::to_string(x)).c_str());
		championList[x] = ChampionDataManager::GetInstance()->LoadChampionById(x);
		championList[x]->SetChampionEXP(ChampionDataManager::GetInstance()->GetChampionEXP(nId, x));
	}
	return championList;
}
Champion* UserDataManager::ReloadSelectedChampion(int userId, int cId)
{
	cocos2d::log("=-----------------------------=");
	auto c = ChampionDataManager::GetInstance()->LoadChampionById(cId);
	c->SetChampionEXP(ChampionDataManager::GetInstance()->GetChampionEXP(userId, cId));
	cocos2d::log("=-----------------------------=");
	return c;
}
void UserDataManager::UpdateUserGameDetails(int nUserId, UserGameDetails* newUGD)
{
	std::string command = "UPDATE user_game_data SET loses_game = " + std::to_string(newUGD->g_nLoseGames) +
		", wins_game = " + std::to_string(newUGD->g_nWinGames) + " WHERE userId = " + std::to_string(nUserId) + ";";
	cocos2d::log("=-----------------------------=");
	if (Database::GetInstance()->GetExec(command)) cocos2d::log("USER DATA MANAGER: Update user game detail successfully");
	else cocos2d::log("USER DATA MANAGER: CANNOT Update user game detail");
	cocos2d::log("=-----------------------------=");
	LogManager::GetInstance()->Log("USER DATA MANAGER: Update user's game details successfully");
}
void UserDataManager::UpdateChampionEXP(int nUserId, int nChampionId, float exp)
{
	std::string command = "UPDATE user_owned_champion SET exp = " + std::to_string(exp);
	std::string command2 = " where userId = " + std::to_string(nUserId) + " AND championId = " + std::to_string(nChampionId) + ";";
	cocos2d::log("=-----------------------------=");
	if (Database::GetInstance()->GetExec(command + command2)) cocos2d::log("USER DATA MANAGER: Update champion exp successfully");
	else cocos2d::log("USER DATA MANAGER: CANNOT Update Update champion exp");
	cocos2d::log("=-----------------------------=");
}
void UserDataManager::UpdateUserEconomy(int nUserId, EconomyUnit* newUGD)
{
	std::string command = "UPDATE user_economy SET xu = " + std::to_string(newUGD->g_fXu) + ", sPoint = " + std::to_string(newUGD->g_fSp);
	std::string command2 = " where userId = " + std::to_string(nUserId) + ";";
	cocos2d::log("=-----------------------------=");
	if (Database::GetInstance()->GetExec(command + command2)) cocos2d::log("USER DATA MANAGER: Update user economy successfully");
	else cocos2d::log("USER DATA MANAGER: CANNOT Update user economy");
	cocos2d::log("=-----------------------------=");
	LogManager::GetInstance()->Log("USER DATA MANAGER: Update user's economy successfully");
}

void UserDataManager::UpdateSelectedChampionId(int nUserId, int newSelectId)
{
	std::string command = "UPDATE user_game_data SET selectedId = " + std::to_string(newSelectId);
	std::string command2 = " WHERE userId = " + std::to_string(nUserId) + ";";
	cocos2d::log("=-----------------------------=");
	if (Database::GetInstance()->GetExec(command + command2)) cocos2d::log("USER DATA MANAGER: Update selected champion id successfully");
	else cocos2d::log("USER DATA MANAGER: CANNOT Update selected champion id");
	cocos2d::log("=-----------------------------=");
	LogManager::GetInstance()->Log("USER DATA MANAGER: Update user's selected champion's id successfully");
}

void UserDataManager::UpdatePassword(int nUserId, std::string s)
{
	std::string command = "UPDATE user_informations SET password = '" + s;
	std::string command2 = "' WHERE userId = " + std::to_string(nUserId) + ";";
	cocos2d::log("=-----------------------------=");
	if (Database::GetInstance()->GetExec(command + command2)) cocos2d::log("USER DATA MANAGER: Update selected champion id successfully");
	else cocos2d::log("USER DATA MANAGER: CANNOT Update selected champion id");
	cocos2d::log("=-----------------------------=");
	LogManager::GetInstance()->Log("USER DATA MANAGER: Update user's password by user's id successfully");

}