#pragma once
#include "cocos2d.h"
#include "Extention/Statics_Attributes.h"
#include <math.h>
#include "GameFight/GameEnvironment.h"
const float PI = 3.14159265f;

class BulletPhysic
{
public:
	BulletPhysic() {};
	~BulletPhysic() = default;
public:
	inline static cocos2d::Point SCalculateStartPoint(cocos2d::Size championSize, cocos2d::Point championPos, cocos2d::Size bulletSize, DIR eChampionDir, float fAngle_R)
	{
		float m_fSafeAngle = atan(championSize.height / championSize.width);

		float fH = championSize.height / 2 + bulletSize.height / 2;
		float fW = championSize.width / 2 + bulletSize.width / 2;
		cocos2d::Point startPoint;
		if (0 <= fAngle_R && fAngle_R < m_fSafeAngle)
		{
			startPoint.x = championPos.x + fW / eChampionDir + 1;
			startPoint.y = championPos.y + tan(fAngle_R) * fW + 1;
		}
		else if (m_fSafeAngle <= fAngle_R && fAngle_R <= PI / 2)
		{
			startPoint.x = championPos.x + tan(PI / 2 - fAngle_R) * (fH / eChampionDir) + 1;
			startPoint.y = championPos.y + fH + 1;
		}
		return startPoint;
	}
public:
	inline cocos2d::Point GetStarterPoint()
	{
		return cocos2d::Point(m_fStartPoint_X, m_fStartPoint_Y);
	}
public:
	virtual cocos2d::Point NextXY(float fTime, float fForce, DIR eChampionDir, float fAngle, float fBulletMass) = 0;
	
	virtual void CalculateStartPoint(cocos2d::Sprite* pChampionSprite, cocos2d::Sprite* pBulletSprite, DIR eChampionDir, float fAngle_R)
	{
		m_fSafeAngle = atan(pChampionSprite->getContentSize().height / pChampionSprite->getContentSize().width);
		float fH = pChampionSprite->getContentSize().height / 2 + pBulletSprite->getContentSize().height / 2;
		float fW = pChampionSprite->getContentSize().width / 2 + pBulletSprite->getContentSize().width / 2 ;
		if (0 <= fAngle_R && fAngle_R < m_fSafeAngle)
		{
			m_fStartPoint_X = pChampionSprite->getPosition().x + fW / eChampionDir + 1;
			m_fStartPoint_Y = pChampionSprite->getPosition().y + tan(fAngle_R) * fW + 1;
		}
		else if (m_fSafeAngle <= fAngle_R && fAngle_R <= PI / 2)
		{
			m_fStartPoint_X = pChampionSprite->getPosition().x + tan(PI / 2 - fAngle_R) * (fH / eChampionDir) + 1;
			m_fStartPoint_Y = pChampionSprite->getPosition().y + fH + 1;
		}
		cocos2d::log(("		>   BULLET PHYSIC: STARTER POINT: " + std::to_string(m_fStartPoint_X) + " - " + std::to_string(m_fStartPoint_Y)).c_str());
		cocos2d::log(("		>	BULLET PHYSIC: CHAMPION POS: " + std::to_string(pChampionSprite->getPosition().x) + " - " + std::to_string(pChampionSprite->getPosition().y)).c_str());
	}
	virtual void CalculateStartPoint(cocos2d::Size championSize, cocos2d::Point championPos, cocos2d::Size bulletSize, DIR eChampionDir, float fAngle_R)
	{
		m_fSafeAngle = atan(championSize.height / championSize.width);
		float fH = championSize.height / 2 + bulletSize.height / 2;
		float fW = championSize.width / 2 + bulletSize.width / 2;

		if (0 <= fAngle_R && fAngle_R < m_fSafeAngle)
		{
			m_fStartPoint_X = championPos.x + fW / eChampionDir + 1;
			m_fStartPoint_Y = championPos.y + tan(fAngle_R) * fW + 1;
		}
		else if (m_fSafeAngle <= fAngle_R && fAngle_R <= PI / 2)
		{
			m_fStartPoint_X = championPos.x + tan(PI / 2 - fAngle_R) * (fH / eChampionDir) + 1;
			m_fStartPoint_Y = championPos.y + fH + 1;
		}
	}
protected:
	float m_fStartPoint_X, m_fStartPoint_Y;
	float m_fSafeAngle;
};

