#pragma once
#include "Extention/Statics_Attributes.h"
#include "Item/Weapon/Weapon.h"
#include "GameObject/GameObject.h"
#include "cocos2d.h"
#include "GameObject/Properties.h"
#include "Extention/DamageManager.h"
#include "Extention/ShopManager.h"
#include "Bullet/Bullet.h"
#include "Extention/Node_StringNTag.h"

class Champion : public GameObject
{
public:
	//std::map<ChampionAction, ChampionDoAction*> g_Bullist;
public:
	Champion(const XProperties* pProperties);
	void Init();
	void SetFlip(DIR edir);
	void log();
	void ConvertAdditionAttributesToStatic(ChampionAttributes* pChampionAttributes);
	void GravityEffect(float gracityAcc, float dt);
	void SuddenDeath();

	virtual void Cleaner();
public:
	virtual void Update(float dt);
public:
	std::map<ChampionAction, std::string> g_mChampionTexture;
	std::map<SkillIndex, std::string> g_mChampionSkillList;
public:
	inline Statics* GetStatics() {  return m_pStatics; }
	inline Statics* GetBaseStatics() { return m_pStatics_Base; }
	inline ChampionAttributes* GetChampionAttributes() { return m_pChampionAttributes; }
	int GetChampionMainAttributes();
	inline ChampionAttributes* GetChampionAttributes_Base() { return m_pChampionAttributes_Base; }
	inline ChampionStatics* GetChampionStatics() {return m_pChampionStatics;}
	inline ShopEconomy* GetChampionEconomy() { return this->m_pChampionEconomy; }
	inline ChampionAction GetChampionAction() { return this->m_eChampionAction; }
	inline float GetChampionEXP() { return this->m_pChampionStatics->g_fEXP; }
	//inline BulletManager* GetBulletManager() { return this->m_pBulletManager; }

	inline void SetChampionStatics(ChampionStatics* pc) { this->m_pChampionStatics = pc; }
	inline void SetTheStatics(Statics* p) { this->m_pStatics_Base = p;  }
	inline void SetBaseChampionAttributes(ChampionAttributes* p) { this->m_pChampionAttributes_Base = p; }
	inline void SetChampionAttributesPerLevel(ChampionAttributes* p) { this->m_pChampionAttributes_LvIncrease = p; }
	inline void SetChampionEXP(float exp) { this->m_pChampionStatics->g_fEXP = exp; }
	inline void SetChampionEconomy(ShopEconomy* pChampionEconomy) { this->m_pChampionEconomy = pChampionEconomy; }
	inline void SetChampionAction(ChampionAction p) { this->m_eChampionAction = p; }

	inline void AddChampionEXP(float exp) { this->m_pChampionStatics->g_fEXP += exp; }
public:
	virtual void DoPassTurn();
	virtual void GetHit(SkillStatics* pSkill);
	virtual void Move(DIR edir, float dt);
	virtual void Respawn(float dt);
	virtual void VoidDetect();
	virtual void EndTurn();
protected:
	void LifeCheck(float dt);
	void ValidStatics();
protected:
	ChampionAttributes* m_pChampionAttributes;
	ChampionAttributes* m_pChampionAttributes_Base, *m_pChampionAttributes_LvIncrease;

	ChampionStatics* m_pChampionStatics;

	Statics* m_pStatics_Base, * m_pStatics;

	std::map<int, Weapon*> m_vEquipedWeaponList;

	ChampionAction m_eChampionAction;
	//std::string m_sBulletTexture;
	//BulletManager* m_pBulletManager;
	//ChampionDoAction m_ChampionDoAction;
	ShopEconomy* m_pChampionEconomy;
	
private:
	void CalculateChampionAttributes();
	void CalculateStatics();
	void Convert_ATT_to_STT();
	void FirstSetSTT();
	void Convert_Strength_to_STT(ChampionAttributes* pChampionAttributes);
	void Convert_Agility_to_STT(ChampionAttributes* pChampionAttributes);
	void Convert_Intelligence_to_STT(ChampionAttributes* pChampionAttributes);
	void AutoLevel();
};

