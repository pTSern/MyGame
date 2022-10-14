#pragma once
#include "cocos2d.h"
#include "Properties.h""

class AGameObject : public cocos2d::Node
{
public:
	AGameObject(const XProperties* pProperties) {};
	//virtual ~AGameObject() = default;
	virtual void Update(float dt) = 0;
};

/*
	
	if (fAngle == PI / 2) wind_X = eChampionDir * GameEnvironment::GetInstance()->GetWindForce() * fTime / fBulletMass;
*/