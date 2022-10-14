#pragma once
#include "Database.h"
#include "Champion/Champion.h"
#include "Extention/Statics_Attributes.h"
#include "ItemData_Manager.h"

class ChampionDataManager
{
public:
	inline static ChampionDataManager* GetInstance()
	{
		return p_pInstance = (p_pInstance != nullptr) ? p_pInstance : new ChampionDataManager();
	}
	Champion* LoadChampionById(int nId);
	float GetChampionEXP(int nUserId, int nChampionId);
private:
	Champion* GetChampionData();
	ChampionStatics* GetChampionStatics();
	ChampionAttributes* GetBaseChampionAttributeById();
	ChampionAttributes* GetChampionAttPerLvById();
	ShopEconomy* GetChampionEconomy();

	Statics* GetTheChampionStatics();

	ChampionDataManager() {}
	static ChampionDataManager* p_pInstance;
};