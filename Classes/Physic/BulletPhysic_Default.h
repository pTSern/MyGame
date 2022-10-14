#pragma once
#include "BulletPhysic.h"
#include "Factory/BulletPhysicFactory.h"

class BulletPhysic_Default : public BulletPhysic
{
public:
	BulletPhysic_Default();
	~BulletPhysic_Default() = default;

	virtual cocos2d::Point NextXY(float fTime, float fForce, DIR eChampionDir, float fAngle, float fBulletMass);
	virtual void CalculateStartPoint(cocos2d::Sprite* pChampionSprite, cocos2d::Sprite* pBulletSprite, DIR eChampionDir, float fAngle);
	virtual void CalculateStartPoint(cocos2d::Size championSize, cocos2d::Point championPos, cocos2d::Size bulletSize, DIR eChampionDir, float fAngle_R);
};

