#include "BulletManager.h"


void BulletManager::Schedule_CreateBullist(float dt)
{
	if (p_fTimer >= this->g_pBulletStatic->g_fShootDelay)
	{
		Bullet* pB = Bullet::Create(g_pChampSkill, g_pBulletStatic->g_sBulletTexture);
		if (pB)
		{
			p_fTimer = 0;

			p_nCreatedNum++;

			g_bullist.push_back(pB);

			//ADD child for running scene
			g_pScene->addChild(g_bullist[g_bullist.size() - 1]);
			g_pScene->setTag(1);
			g_bullist[g_bullist.size() - 1]->GetSprite()->setGlobalZOrder(1);
			g_pBulletPhysic->CalculateStartPoint(g_pChampion->GetSprite(), g_bullist[g_bullist.size() - 1]->GetSprite(), g_pPlayerStatics->g_eDir, g_pPlayerStatics->g_fAngle * PI / 180);
		}
	}
	else p_fTimer += dt;
	//cocos2d::log(std::to_string(p_fTimer).c_str());
	if (p_nCreatedNum == this->g_pBulletStatic->g_nBulletNum)
	{
		g_bIsFinishCreateBullet = true;
	}

}
void BulletManager::Call()
{
	//g_pScene->schedule(CC_SCHEDULE_SELECTOR(BulletManager::Schedule_Checker), 0);
	
	//g_pScene->schedule(CC_SCHEDULE_SELECTOR(BulletManager::Schedule_CreateBullist), this->g_pBulletStatic->g_fShootDelay);
	
	//g_pScene->schedule(CC_SCHEDULE_SELECTOR(BulletManager::Schedule_Shooting), 0);
	this->Reset();
	g_bIsCalled = true;
	//cocos2d::log("CALLLLLLLLL SKILLLLLLLLLLLLLLLLL");
}
void BulletManager::Running(float dt)
{
	if (g_bIsCalled)
	{
		//cocos2d::log("RUNNINGGGGGGG SHOOTINNNNN");
		if (!g_bIsFinishCreateBullet) Schedule_CreateBullist(dt);
		if (p_nDestroyedNum != this->g_pBulletStatic->g_nBulletNum)
		{
			Schedule_Shooting(dt);
		}
		else
		{
			g_bIsFinishShoot = true;
			
		}
	}
}
void BulletManager::Schedule_Checker(float dt)
{
	if (g_bIsFinishCreateBullet)
	{
		//g_pScene->unschedule(CC_SCHEDULE_SELECTOR(BulletManager::Schedule_CreateBullist));
	}

	if (p_nDestroyedNum == this->g_pBulletStatic->g_nBulletNum)
	{
		g_bIsFinishShoot = true;
		//g_pScene->unschedule(CC_SCHEDULE_SELECTOR(BulletManager::Schedule_Shooting));
		//g_pScene->unschedule(CC_SCHEDULE_SELECTOR(BulletManager::Schedule_Checker));
		this->Reset();
	}
}

void BulletManager::Shooting(float dt)
{
	for (int i = 0; i < g_bullist.size(); i++)
	{
		g_bullist[i]->update(dt);
		g_bullist[i]->AutoRotation(dt);
		g_bullist[i]->AutoIncreaseTime(dt);
		
		g_bullist[i]->SetPosition(g_pBulletPhysic->NextXY(dt, g_pPlayerStatics->g_fForceMemory, g_pPlayerStatics->g_eDir, g_pPlayerStatics->g_fAngle, g_bullist[i]->GetMass()));
		
		if (CheckReachVoid(g_bullist[i]))
		{
			g_pScene->removeChild(g_bullist[i], true);
			g_bullist.erase(g_bullist.begin() + i);
			p_nDestroyedNum++;
			//cocos2d::log(("BULLET OUT OF RANGE"));
		}
	}
	cocos2d::log("SCHEDULE SHOOTING");
}
void BulletManager::Schedule_Shooting(float dt)
{
	for (int i = 0; i < g_bullist.size(); i++)
	{
		g_bullist[i]->Update(dt);
		g_bullist[i]->AutoRotation(dt);
		g_bullist[i]->AutoIncreaseTime(dt);

		g_bullist[i]->SetPosition(g_pBulletPhysic->NextXY(g_bullist[i]->GetTime(), g_pPlayerStatics->g_fForceMemory, g_pPlayerStatics->g_eDir, g_pPlayerStatics->g_fAngle*PI/180, g_bullist[i]->GetMass()));
		g_bullist[i]->Rotate();
		//cocos2d::log(("BULLET " + std::to_string(g_bullist[i]->GetPosition().x) + " - " + std::to_string(g_bullist[i]->GetPosition().y)).c_str());
		if (CheckReachSideMap(g_bullist[i]) || CheckReachVoid(g_bullist[i]) || CheckContactMapCollision(g_bullist[i]) || CheckContactPlayer(g_bullist[i]))
		{
			g_pScene->removeChild(g_bullist[i], true);
			g_bullist.erase(g_bullist.begin() + i);
			p_nDestroyedNum++;
		}
	}
	//cocos2d::log("SCHEDULE SHOOTING");
}
bool BulletManager::CheckContactPlayer(Bullet* bullet)
{
	if (bullet->IsContactPlayer())
	{
		SoundManager::GetInstance()->PlaySoundEffect("audio/hero/bullet_contact.mp3");
		return true;
	}
	return false;
}
bool BulletManager::CheckReachVoid(Bullet* bullet)
{
	if (bullet->GetSprite()->getPosition().y > MapManager::GetInstance()->GetMapSize().height * 3 || bullet->GetSprite()->getPosition().y <= 0) return true;
	return false;
}

void BulletManager::Schedule_OnContactBegin(cocos2d::PhysicsContact& contact)
{
	auto pNodeA = contact.getShapeA()->getBody()->getNode();
	auto pNodeB = contact.getShapeB()->getBody()->getNode();
	for (int i = 0; i < g_bullist.size(); i++)
	{
		if (g_bullist[i]->GetSprite() == pNodeA)
		{
			if (pNodeA->getName() != pNodeB->getName()) //Check If node have same name or not
			{
				//dynamic_cast<Champion*>(pNodeB)->GetHit(g_pChampSkill);
				g_pScene->removeChild(g_bullist[i]->GetSprite());
				g_bullist.erase(g_bullist.begin() + i);
				p_nDestroyedNum++;
				break;
			}
		}
	}
}
bool BulletManager::CheckContactMapCollision(Bullet* bullet)
{
	if (bullet->IsThroughMap()) return false;
	if (bullet->GetPosition().y <= MapManager::GetInstance()->GetMapSize().height && MapManager::GetInstance()->CheckMapCollision(bullet->GetPosition(), bullet->GetContentSzie()))
	{
		SoundManager::GetInstance()->PlaySoundEffect("audio/hero/bullet_contact.mp3");
		return true;
	}
	return false;
}
bool BulletManager::CheckReachSideMap(Bullet* bullet)
{
	if (bullet->IsBouncing()) return false;
	if (MapManager::GetInstance()->IsReachSideMap(bullet->GetPosition(), bullet->GetContentSzie()))
	{
		return true;
	}
	return false;
}
void BulletManager::Reset()
{
	this->p_fTimer = this->g_pBulletStatic->g_fShootDelay;
	p_nCreatedNum = 0, p_nDestroyedNum = 0;
	g_bIsFinishCreateBullet = false, g_bIsFinishShoot = false;
	g_bIsCalled = false;
	cocos2d::log("     BULLET MANAGER: RESETTTTTT ALLLLLLLL");
}
void BulletManager::Cleaner()
{
	for (auto& x : g_bullist)
		x->Cleaner();
	
	for (auto& x : g_bullist)
		CC_SAFE_DELETE(x);

	CC_SAFE_DELETE(g_pScene);
	CC_SAFE_DELETE(g_pBulletPhysic);
	CC_SAFE_DELETE(g_pPlayerStatics);
	//CC_SAFE_DELETE(g_pChampSkill);
	CC_SAFE_DELETE(g_pChampion);
	CC_SAFE_DELETE(g_pBulletStatic);

}
void BulletManager::BulletContactPlayer(Bullet *pB)
{
	g_pScene->removeChild(pB);
	p_nDestroyedNum++;
}