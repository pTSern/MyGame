#pragma once
#include "Champion/Champion.h"
#include "Factory/GameObjectFactory.h"
class Hero : public Champion
{
public:
	Hero(const XProperties* pProperties);
public:
	virtual void Update(float dt);
public:
	virtual void DoPassTurn();
	virtual void GetHit(SkillStatics* pSkill);
	virtual void Move(DIR edir, float dt);

	virtual void Respawn(float dt);
	virtual void VoidDetect();
	virtual void EndTurn();
	virtual void Cleaner();
};

