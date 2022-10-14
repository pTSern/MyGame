#pragma once
#include "Skill/SkillType/SkillType.h"
#include "Factory/SkillTypeFactory.h"
class RunAnimationSkill : public SkillType
{
public:
	RunAnimationSkill();
	virtual void Update(float dt);
	virtual void RunAction();
	virtual void Cleaner();
	virtual bool IsFinish();
};

