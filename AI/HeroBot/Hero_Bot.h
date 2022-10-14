#include "Factory/Bot_Factory.h"
class Hero_Bot : public AI
{
public:
	Hero_Bot();
public:
	virtual void Move();
	virtual void Skill();
	virtual float ForceCalculate(DIR g_eDir, float g_fAngle, float g_fMass, cocos2d::Point posP, cocos2d::Point posB, float g_fMaxForce);
};