#pragma once
#include "Extention/Statics_Attributes.h"
#include "Item/Item.h"
#include "Extention/ItemManager.h"

enum WeaponType
{
	MAIN = 0,
	SUB = 1,
	ARMOR = 2,
	ARTIFACT = 3
};

class Weapon : public Item
{
public:
	Weapon(const XProperties* pProperties);
	ChampionAttributes* GetChampionAttributes(){ return g_pAttributes; }
	Statics* GetStatics() {return g_pStatics; }
public:
	virtual void Update(float dt);
	virtual void Cleaner();
public:
	ChampionAttributes* g_pAttributes;
	WeaponType g_weaponType;
	Statics* g_pStatics;
	bool g_bIsForceChampion;
	int g_nChampionID;
	void log()
	{
		//cocos2d::log(("Str: " + std::to_string(this->g_pAttributes->g_fStrength)).c_str());
		//cocos2d::log(("Agi: " + std::to_string(this->g_pAttributes->g_fAgility)).c_str());
		//cocos2d::log(("Int: " + std::to_string(this->g_pAttributes->g_fIntelligence)).c_str());
		
		cocos2d::log(("Sprite: " + this->GetSText()).c_str());
		//cocos2d::log(("Dmg: " + std::to_string(this->g_pStatics->g_fATK)).c_str());
	}

	void ConvertFromIten(Item* i);
};

