#pragma once
#include "Skill/Skill.h"
#include "Factory/SkillFactory.h"
class PassiveSkill : public Skill
{
public:
	PassiveSkill();
public:
	virtual void Cleaner();
};
