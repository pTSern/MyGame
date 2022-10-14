#pragma once
#include "Bullet/Bullet.h"
#include "cocos2d.h"
#include "CCRef.h"
#include "Extention/Node_StringNTag.h"
#include "Extention/PlayerManager.h"
#include "Factory/BulletPhysicFactory.h"
#include "Champion/Champion.h"
#include "Map/Map.h"
#include "GameFight/BattleElement.h"
#include "Audio/SoundManager.h"

class BulletManager
{
public:
	bool g_bIsCalled = false;
	BulletManager(BulletStatic* pBulletS, BulletElement* pBL, SkillStatics* pChampS,Champion* pChampion)
	{
		this->g_pScene = BattleElement::GetInstance()->GetBattleScene();
		this->g_pChampion = pChampion;
		this->g_pChampSkill = pChampS;
		this->g_pBulletStatic = pBulletS;
		this->g_pBulletElement = pBL;
		//this->g_pPlayerStatics = pPlayerStatics;
		g_pBulletPhysic = BulletPhysicFactory::GetInstance()->Create(pBulletS->g_sPhysicType);

		
	}
	
public:
	void Call();
	void Running(float dt);
	inline void SetPlayerStatics(PlayerStatics* pPlayerStatics)
	{
		this->g_pPlayerStatics = pPlayerStatics;
	}
	inline bool IsFinish()
	{
		return this->g_bIsFinishShoot;
	}
public:
	std::vector<Bullet*> g_bullist;

	cocos2d::Node* g_pScene;
	BulletPhysic* g_pBulletPhysic;

	PlayerStatics *g_pPlayerStatics;
	SkillStatics* g_pChampSkill;
	Champion *g_pChampion;
	BulletStatic* g_pBulletStatic;
	BulletElement* g_pBulletElement;
	bool g_bIsFinishCreateBullet = false, g_bIsFinishShoot = false;

public:
	bool CheckReachVoid(Bullet* bullet);
	void BulletContactPlayer(Bullet* pB);
	void Reset();
	
	void Shooting(float dt);
	void Schedule_CreateBullist(float dt);
	void Schedule_Shooting(float dt);
	void Schedule_Checker(float dt);

	bool CheckContactMapCollision(Bullet* bullet);
	bool CheckReachSideMap(Bullet* bullet);
	bool CheckContactPlayer(Bullet* bullet);

	void Cleaner();
	/*A fucntion trigger when a physic contact is triggered, this function
	is created for a schedule function that will loop a certain time with a certain delay*/
	void Schedule_OnContactBegin(cocos2d::PhysicsContact& contact);
private:
	cocos2d::Sprite* p_pChampionSprite;
	int p_nCreatedNum = 0, p_nDestroyedNum = 0;
	float p_fTimer;
};