#pragma once
#include "Skill/SkillType/SkillType.h"
#include "ObjectManager/BulletManager.h"
#include "Factory/SkillTypeFactory.h"

class ShootBulletSkill : public SkillType 
{
public:
	ShootBulletSkill();
	virtual void Update(float dt);
	virtual void RunAction();
	virtual void Cleaner();
	virtual bool IsFinish();
public:
	//void Init(Champion* pChampion, SkillStatics* pChampS, PlayerStatics* pPlayerStatics, int nBulletNum, std::string sPhysicType, std::string sBulletTexture, float fShootDelay);
	void Init(BulletStatic* pBulletS, BulletElement* pBL, SkillStatics* pChampS, Champion* pChampion);
	inline void SetPlayerStatics(PlayerStatics* pPlayerStatics)
	{
		this->g_pPlayerStatics = pPlayerStatics;
	}
public:
	BulletManager* g_pBulletManager;
	//BulletStatic* g_BulletStatic;
	PlayerStatics* g_pPlayerStatics;
};

