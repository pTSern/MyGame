#pragma once
#include "Skill/TriggerCondition/TriggerCondition.h"
class OnHit : public TriggerCondition
{
public:
	virtual bool ConditionMatch()
	{
		return this->m_bIsMatchCondition;
	}
	virtual void AutoCheckCondition();
	virtual void CallCheckCondition();
	virtual void Cleaner();
};
