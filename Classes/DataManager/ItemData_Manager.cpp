#include "ItemData_Manager.h"

ItemDataManager* ItemDataManager::sp_pInstance = nullptr;

ItemDataManager::ItemDataManager()
{
}

Item* ItemDataManager::GetItemById(int nId)
{
	std::string cmd = "SELECT item.itemId, item.name, item.texture_file, item.description, item.stackId, item.tierId, item_type.type, shop_sale.sale_xu, shop_sale.sale_sp, shop_economy.price_xu, shop_economy.price_sp, item.is_for_sale";
	std::string cmd1 = " FROM item INNER JOIN shop_sale ON shop_sale.shop_sale_Id = item.item_sale_Id INNER JOIN shop_economy ON shop_economy.shop_eco_Id = item.item_price_Id INNER JOIN item_type ON item_type.item_type_Id = item.item_type_Id WHERE item.itemId = " + std::to_string(nId);
	Item* i = nullptr;
	if (Database::GetInstance()->GetPrepareV2(cmd + cmd1))
	{
		int result = sqlite3_step(Database::GetInstance()->GetStatement());
		if (result == SQLITE_ROW)
		{
			i = this->GetItemData();
		}
	}
	return i;
}

std::map<int, Item*> ItemDataManager::GetItemShopList()
{
	std::string cmd = "SELECT * FROM item WHERE is_sell = TRUE AND";
	std::map<int, Item*> mShopList;
	if (this->DatabaseConnectionPrepare(cmd))
	{
		int result = 0;
		while (true)
		{
			int result = sqlite3_step(Database::GetInstance()->GetStatement());
			if (result == SQLITE_ROW)
			{
				mShopList[sqlite3_column_int(Database::GetInstance()->GetStatement(), 0)] = GetItemData();
			}
			else break;
		}
	}
	return mShopList;
}

Item* ItemDataManager::GetItemData()
{
	XProperties* pPro = new XProperties(std::string(reinterpret_cast<const char*>(sqlite3_column_text(Database::GetInstance()->GetStatement(), 2))), 0, 0, false);
	GameObject* pGO = GameObjectFactory::GetInstance()->Create(std::string(reinterpret_cast<const char*>(sqlite3_column_text(Database::GetInstance()->GetStatement(), 6))), pPro);
	Item* i = dynamic_cast<Item*>(pGO);
	ShopEconomy* pEco = new ShopEconomy
	(
		sqlite3_column_double(Database::GetInstance()->GetStatement(), 9),
		sqlite3_column_double(Database::GetInstance()->GetStatement(), 10),
		(bool)sqlite3_column_int(Database::GetInstance()->GetStatement(), 11),
		sqlite3_column_double(Database::GetInstance()->GetStatement(), 7),
		sqlite3_column_double(Database::GetInstance()->GetStatement(), 8)
	);
	
	ItemStatics* is = new ItemStatics
	(
		sqlite3_column_int(Database::GetInstance()->GetStatement(), 0),
		std::string(reinterpret_cast<const char*>(sqlite3_column_text(Database::GetInstance()->GetStatement(), 1))),
		std::string(reinterpret_cast<const char*>(sqlite3_column_text(Database::GetInstance()->GetStatement(), 3))),
		(ItemTiers)sqlite3_column_int(Database::GetInstance()->GetStatement(), 5),
		(ItemStackType)sqlite3_column_int(Database::GetInstance()->GetStatement(), 4)
	);
	i->SetItemStatics(is);
	i->SetItemEconomy(pEco);
	return i;
}

Weapon* ItemDataManager::GetWeaponById(int nId)
{
	Item* i = (this->GetItemById(nId));
	std::string cmd = "SELECT weapon.staticId, weapon.is_force_champion, weapon.championId, weapon.weapon_type_Id";
	std::string cmd1 = ", statics.atk, statics.max_hp, statics.regen_hp, statics.max_stamina, statics.regen_stamina, statics.armor, statics.spell_amp, statics.spell_res, statics.speed, statics.lifesteal, statics.spell_lifesteal";
	std::string cmd2 = ", base_attribute.att_str, base_attribute.att_agi, base_attribute.att_int FROM weapon";
	std::string cmd3 = " INNER JOIN statics ON weapon.staticId = statics.staticId INNER JOIN base_attribute ON base_attribute.base_att_Id = weapon.base_att_Id";
	std::string cmd4 = " WHERE weapon.weaponId = " + std::to_string(nId);

	if (i != nullptr && Database::GetInstance()->GetPrepareV2(cmd + cmd1 + cmd2 + cmd3 + cmd4))
	{
		int result = sqlite3_step(Database::GetInstance()->GetStatement());
		if (result == SQLITE_ROW)
		{
			return this->GetWeaponData(i);
		}
	}
	return nullptr;
}

Weapon* ItemDataManager::GetWeaponData(Item *i)
{
	Weapon* w = reinterpret_cast<Weapon*>(i);
	w->g_bIsForceChampion = (bool)sqlite3_column_int(Database::GetInstance()->GetStatement(), 1);
	w->g_nChampionID = sqlite3_column_int(Database::GetInstance()->GetStatement(), 2);
	w->g_weaponType = (WeaponType)sqlite3_column_int(Database::GetInstance()->GetStatement(), 3);
	w->g_pStatics = this->GetWeaponStatic();
	w->g_pAttributes = this->GetWeaponAttributes();
	//w->g_pAttributes = this->GetWeaponAttributes();
	return w;
}
ChampionAttributes* ItemDataManager::GetWeaponAttributes()
{
	ChampionAttributes* pCA = new ChampionAttributes
	(
		sqlite3_column_double(Database::GetInstance()->GetStatement(), 22),
		sqlite3_column_double(Database::GetInstance()->GetStatement(), 23),
		sqlite3_column_double(Database::GetInstance()->GetStatement(), 24)
	);
	return pCA;
}
Statics* ItemDataManager::GetWeaponStatic()
{
	Statics* pStatic = new (std::nothrow) Statics
	(
		sqlite3_column_double(Database::GetInstance()->GetStatement(), 4),
		sqlite3_column_double(Database::GetInstance()->GetStatement(), 5),
		sqlite3_column_double(Database::GetInstance()->GetStatement(), 6),
		sqlite3_column_double(Database::GetInstance()->GetStatement(), 7),
		sqlite3_column_double(Database::GetInstance()->GetStatement(), 8),
		sqlite3_column_double(Database::GetInstance()->GetStatement(), 9),
		sqlite3_column_double(Database::GetInstance()->GetStatement(), 10),
		sqlite3_column_double(Database::GetInstance()->GetStatement(), 11),
		sqlite3_column_double(Database::GetInstance()->GetStatement(), 12),
		sqlite3_column_double(Database::GetInstance()->GetStatement(), 13),
		sqlite3_column_double(Database::GetInstance()->GetStatement(), 14)
	);
	return pStatic;
}

bool ItemDataManager::DatabaseConnectionPrepare(std::string cmd)
{
	bool b = false;
	if (Database::GetInstance()->OpenConnection())
	{
		if (Database::GetInstance()->GetPrepareV2(cmd))
		{
			b = true;
		}
		Database::GetInstance()->CloseConnection();
	}
	return b;
}