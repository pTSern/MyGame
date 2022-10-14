#pragma once
#include "cocos2d.h"
#include "ChampionSkill/ChampionSkill.h"
#include "Factory/ChampionSkillFacatory.h"
class Hero_NormalAttack : public ChampionSkill
{
public:
	Hero_NormalAttack(Champion* pOwner, PlayerStatics* pPlayerStatics);
public:
	virtual void Init();
	virtual void Update(float dt);
	virtual bool CheckerTriggerCondition();
	virtual void SkillMechanic();
	virtual void RecaculateSkill();
	virtual void TriggerSkill();
	virtual void Cleaner();
	virtual bool IsFinish();
};