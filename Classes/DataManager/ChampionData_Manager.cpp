#include "ChampionData_Manager.h"
ChampionDataManager* ChampionDataManager::p_pInstance = nullptr;

Champion* ChampionDataManager::LoadChampionById(int nId)
{
	std::string cmd = "SELECT base_champion.texture_file, base_champion.base_championId, base_champion.main_att_Id, base_champion.name, base_champion.min_angle, base_champion.max_angle, base_champion.max_force, base_champion.mass, shop_economy.price_xu, shop_economy.price_sp, base_champion.life";
	std::string cmd2 = ", statics.atk, statics.max_hp, statics.regen_hp, statics.max_stamina, statics.regen_stamina, statics.armor, statics.spell_amp, statics.spell_res, statics.speed, statics.lifesteal, statics.spell_lifesteal, base_attribute.att_str, base_attribute.att_agi, base_attribute.att_int, champion_type.type, shop_economy.price_type_Id";
	std::string cmd2_5_0 = ", attribute_per_level.str_per_lv, attribute_per_level.agi_per_lv, attribute_per_level.int_per_lv FROM base_champion";
	std::string cmd2_5_1 = " INNER JOIN statics ON base_champion.base_static_Id = statics.staticId INNER JOIN base_attribute ON base_champion.base_att_Id = base_attribute.base_att_Id INNER JOIN attribute_per_level ON attribute_per_level.championId = base_champion.base_championId";
	std::string cmd2_5_2 = " INNER JOIN champion_type ON base_champion.champion_type_Id = champion_type.ct_Id INNER JOIN shop_economy ON base_champion.champion_eco_Id = shop_economy.shop_eco_Id";
	std::string cmd3 = " WHERE base_champion.base_championId = " + std::to_string(nId);
	Champion* c = nullptr;
	if (Database::GetInstance()->GetPrepareV2(cmd + cmd2 + cmd2_5_0 + cmd2_5_1 + cmd2_5_2 + cmd3))
	{
		int result = sqlite3_step(Database::GetInstance()->GetStatement());
		cocos2d::log(("CHAMPION DATA MANAGER: RESULT " + std::to_string(result)).c_str());
		if (result == SQLITE_ROW)
		{
			c = this->GetChampionData();
		}
	}
	return c;
}
ChampionAttributes* ChampionDataManager::GetBaseChampionAttributeById()
{
	ChampionAttributes* pCA = new ChampionAttributes(
		sqlite3_column_double(Database::GetInstance()->GetStatement(), 22),
		sqlite3_column_double(Database::GetInstance()->GetStatement(), 23),
		sqlite3_column_double(Database::GetInstance()->GetStatement(), 24)
	);

	return pCA;
}
ChampionAttributes* ChampionDataManager::GetChampionAttPerLvById()
{
	ChampionAttributes* pChampionAtt = new ChampionAttributes
	(
		sqlite3_column_double(Database::GetInstance()->GetStatement(), 27),
		sqlite3_column_double(Database::GetInstance()->GetStatement(), 28),
		sqlite3_column_double(Database::GetInstance()->GetStatement(), 29)
	);
	return pChampionAtt;
}
ShopEconomy* ChampionDataManager::GetChampionEconomy()
{
	ShopEconomy* pEco = new ShopEconomy
	(
		sqlite3_column_double(Database::GetInstance()->GetStatement(), 8),
		sqlite3_column_double(Database::GetInstance()->GetStatement(), 9)
	);
	return pEco;
}

Champion* ChampionDataManager::GetChampionData()
{
	ChampionStatics* pCs = this->GetChampionStatics();
	cocos2d::log("FINISH LOAD CHAMPION STATICS");

	XProperties* pPro = new XProperties(std::string(reinterpret_cast<const char*>(sqlite3_column_text(Database::GetInstance()->GetStatement(), 0))), 0, 0, true);
	GameObject* pGO = GameObjectFactory::GetInstance()->Create(std::string(reinterpret_cast<const char*>(sqlite3_column_text(Database::GetInstance()->GetStatement(), 25))), pPro);
	XProperties::Cleaner(pPro);

	cocos2d::log("FINISH PROPERPTIES");
	Champion* c = dynamic_cast<Champion*>(pGO);
	c->SetChampionStatics(pCs);
	cocos2d::log("FINISH CHAMPION STATICS");
	c->SetTheStatics(this->GetTheChampionStatics());
	cocos2d::log("FINISH THE STATICS");
	c->SetBaseChampionAttributes(this->GetBaseChampionAttributeById());
	cocos2d::log("FINISH GET BASE CHAMPION ATT");
	c->SetChampionAttributesPerLevel(this->GetChampionAttPerLvById());
	cocos2d::log("FINISH GET ATT PER LV");
	c->SetChampionEconomy(this->GetChampionEconomy());
	cocos2d::log("FINISH GET CHAMPION ECONOMY");
	return c;
}
ChampionStatics* ChampionDataManager::GetChampionStatics()
{
	ChampionStatics* pCS = new ChampionStatics
	(
		sqlite3_column_int(Database::GetInstance()->GetStatement(), 1),
		(TheAttribute)sqlite3_column_int(Database::GetInstance()->GetStatement(), 2),
		std::string(reinterpret_cast<const char*>(sqlite3_column_text(Database::GetInstance()->GetStatement(), 3))),
		sqlite3_column_int(Database::GetInstance()->GetStatement(), 4),
		sqlite3_column_int(Database::GetInstance()->GetStatement(), 5),
		sqlite3_column_int(Database::GetInstance()->GetStatement(), 6),
		sqlite3_column_double(Database::GetInstance()->GetStatement(), 7),
		sqlite3_column_int(Database::GetInstance()->GetStatement(), 10)
	);
	return pCS;
}
Statics* ChampionDataManager::GetTheChampionStatics()
{
	Statics* pStatic = new (std::nothrow) Statics
	(
		sqlite3_column_double(Database::GetInstance()->GetStatement(), 11),
		sqlite3_column_double(Database::GetInstance()->GetStatement(), 12),
		sqlite3_column_double(Database::GetInstance()->GetStatement(), 13),
		sqlite3_column_double(Database::GetInstance()->GetStatement(), 14),
		sqlite3_column_double(Database::GetInstance()->GetStatement(), 15),
		sqlite3_column_double(Database::GetInstance()->GetStatement(), 16),
		sqlite3_column_double(Database::GetInstance()->GetStatement(), 17),
		sqlite3_column_double(Database::GetInstance()->GetStatement(), 18),
		sqlite3_column_double(Database::GetInstance()->GetStatement(), 19),
		sqlite3_column_double(Database::GetInstance()->GetStatement(), 20),
		sqlite3_column_double(Database::GetInstance()->GetStatement(), 21)
	);
	return pStatic;
}

float ChampionDataManager::GetChampionEXP(int nUserId, int nChampionId)
{
	float exp;
	std::string cmd = "SELECT exp FROM user_owned_champion WHERE userId = " + std::to_string(nUserId) + " AND championId = " + std::to_string(nChampionId);
	if (Database::GetInstance()->GetPrepareV2(cmd))
	{
		int result = sqlite3_step(Database::GetInstance()->GetStatement());
		if (result == SQLITE_ROW)
		{
			exp = sqlite3_column_double(Database::GetInstance()->GetStatement(), 0);
			return exp;
		}
	}
	return 0;
}

