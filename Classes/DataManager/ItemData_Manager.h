#pragma once
#include "Database.h"
#include "cocos2d.h"
#include "Item/Item.h"
#include "Factory/GameObjectFactory.h"
#include "Item/Weapon/Weapon.h"
#include "Extention/Statics_Attributes.h"

class ItemDataManager
{
public:
	inline static ItemDataManager* GetInstance()
	{
		return sp_pInstance = (sp_pInstance != nullptr) ? sp_pInstance : new ItemDataManager();
	}
	inline std::map<int, Item*> GetItemList()
	{
		return this->p_mItemList;
	}
public:
	Item* GetItemById(int nId);
	Weapon* GetWeaponById(int nId);
	
private:
	ItemDataManager();

	Item* GetItemData();
	Weapon* GetWeaponData(Item *i);
	Statics* GetWeaponStatic();
	ChampionAttributes* GetWeaponAttributes();
	std::map<int, Item*> GetItemShopList();

	bool DatabaseConnectionPrepare(std::string cmd);
private:
	std::map<int, Item*> p_mItemList;
	static ItemDataManager* sp_pInstance;
};