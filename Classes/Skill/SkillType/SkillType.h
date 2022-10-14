#pragma once
class SkillType
{
public:
	SkillType() {}
	virtual void Update(float dt) = 0;
	virtual void RunAction() = 0;
	virtual void Cleaner() = 0;
	virtual bool IsFinish() = 0;
};

