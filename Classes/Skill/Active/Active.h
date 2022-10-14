#pragma once
#include "Skill/Skill.h"
#include "Factory/SkillFactory.h"
class ActiveSkill : public Skill
{
public:
	ActiveSkill();
public:
	virtual void Cleaner();
};
