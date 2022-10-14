#pragma once
#include "cocos2d.h"

#include "Champion/Champion.h"
#include "Extention/PlayerManager.h"

#include "Factory/SkillFactory.h"
#include "Factory/SkillTypeFactory.h"
#include "Factory/SkillTriggerCondition.h"
#include "Audio/SoundManager.h"
class ChampionSkill
{
public:
	ChampionSkill(Champion* pOwner, PlayerStatics* pPlayerStatics)
	{
		this->m_pCaster = pOwner;
		this->m_pPlayerStatics = pPlayerStatics;
		//m_pSkill = new Skill();
		m_bIsFinish = false;
		cocos2d::log("CONTRUCTOR CHAMPION SKILL");
	}
public:
	virtual void Init() = 0;
	virtual void Cleaner()
	{
		//CC_SAFE_DELETE(m_pCaster);
		m_pSkill->Cleaner();
		m_pSkill->release();
		//CC_SAFE_DELETE(m_pSkill);

		m_pTriggerCondition->Cleaner();
		CC_SAFE_DELETE(m_pTriggerCondition);
		CC_SAFE_DELETE(m_pPlayerStatics);
	}
	virtual void Update(float dt) = 0;
	virtual bool CheckerTriggerCondition() = 0;
	virtual void SkillMechanic() = 0;
	virtual void RecaculateSkill() = 0;
	virtual void TriggerSkill() = 0;
	virtual bool IsFinish() = 0;
protected:
	//Player* m_pCaster;
	Champion* m_pCaster;
	Skill* m_pSkill;
	TriggerCondition* m_pTriggerCondition;
	SkillType* m_pSkillType;
	PlayerStatics* m_pPlayerStatics;

	bool m_bIsFinish;
};