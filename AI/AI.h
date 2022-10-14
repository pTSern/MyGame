#pragma once
#include <cocos2d.h>
#include <cmath>
#include "Champion/Champion.h"
#include "GameFight/GameEnvironment.h"
#include "Extention/Statics_Attributes.h"
#include "Map/Map.h"
#include "Physic/BulletPhysic.h"

enum class ErorDetect
{
	OUT_OF_FORCE = -1,
	INVALID_DELTA = -2,
	INVALID_TIME = -3,
	OUT_OF_MAP = -4
};

class AI
{
public:
	AI(){}
public:
	virtual void Move() = 0;
	virtual void Skill() = 0;
	virtual float ForceCalculate(DIR g_eDir, float g_fAngle, float g_fMass, cocos2d::Point posP, cocos2d::Point posB, float g_fMaxForce) = 0;
protected:
	cocos2d::Size m_BulletSize, m_ChampionSize;
};

