#pragma once
#include "Skill/TriggerCondition/TriggerCondition.h"
#include "Factory/SkillTriggerCondition.h"
class AlwayActive : public TriggerCondition
{
public:
	AlwayActive();
	virtual bool ConditionMatch()
	{
		return this->m_bIsMatchCondition;
	}
	virtual void AutoCheckCondition();
	virtual void CallCheckCondition();
};