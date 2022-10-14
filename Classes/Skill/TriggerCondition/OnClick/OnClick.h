#pragma once
#include "Skill/TriggerCondition/TriggerCondition.h"
#include "Factory/SkillTriggerCondition.h"
class OnClick : public TriggerCondition
{
public:
	OnClick();
	virtual bool ConditionMatch();
	virtual void AutoCheckCondition();
	virtual void CallCheckCondition();
	virtual void Cleaner();
};
