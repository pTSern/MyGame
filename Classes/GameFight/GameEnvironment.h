#pragma once
#include "cocos2d.h"
#include "Extention/Statics_Attributes.h"
//#include "GameFight/BattleElement.h"
class GameEnvironment
{
public:
	inline static GameEnvironment* GetInstance()
	{
		return sp_pInstance = (sp_pInstance != nullptr) ? sp_pInstance : new GameEnvironment();
	}

	inline int GetWindForce()
	{
		return p_nWindFroce;
	}

	inline DIR GetWindDir()
	{
		return p_eWindDir;
	}

	inline float GetGravityAcceleration()
	{
		return p_fGravityAcceleration;
	}
	inline cocos2d::Node* GetWindTexture()
	{
		return this->p_pNode;
	}
	void Init()
	{
		p_pNode = cocos2d::Node::create();

		p_pWindTexture = cocos2d::Sprite::create("ui/wind.png");
		p_pWindTexture->setPosition(1024 / 2, 768 - p_pWindTexture->getContentSize().height / 2);
		p_pWindTexture->setGlobalZOrder(-2);

		p_pWindForceText = cocos2d::Label::createWithTTF("", "fonts/arial.ttf", 20);
		p_pWindForceText->setPosition(p_pWindTexture->getPosition());
		p_pWindForceText->setGlobalZOrder(-1);
		p_pWindForceText->setTextColor(cocos2d::Color4B::RED);

		p_pNode->addChild(p_pWindTexture);
		p_pNode->addChild(p_pWindForceText);
	}
public:
	void GenerateWindForce();
private:
	GameEnvironment() 
	{
		
	}
	int p_nWindFroce = 0, p_fGravityAcceleration = -1.0;
	DIR p_eWindDir = RIGHT;

	static GameEnvironment* sp_pInstance;

	cocos2d::Sprite* p_pWindTexture;
	cocos2d::Node* p_pNode;
	cocos2d::Label* p_pWindForceText;
};

/*

	float wind_X = GameEnvironment::GetInstance()->GetWindForce() * cos(fAngle) * fTime / fBulletMass;
	if (fAngle == PI / 2) wind_X = GameEnvironment::GetInstance()->GetWindForce() * fTime;

*/