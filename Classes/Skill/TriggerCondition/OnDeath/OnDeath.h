#pragma once
#include "Skill/TriggerCondition/TriggerCondition.h"
#include "Factory/SkillTriggerCondition.h"
class OnDeath : public TriggerCondition
{
public:
	OnDeath();
	virtual bool ConditionMatch()
	{
		return this->m_bIsMatchCondition;
	}
	virtual void AutoCheckCondition();
	virtual void CallCheckCondition();
	virtual void Cleaner();
};
