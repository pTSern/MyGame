#pragma once
#include "Skill/Skill.h"
#include "Factory/SkillFactory.h"
class ToggleSkill : public Skill
{
public:
	ToggleSkill(std::string sTexture);
public:
	virtual void Update(float dt);
	virtual void DoSkill(float dt);
	virtual void RecaculateSkill();
	virtual void Checker_TriggerCondition();
};
