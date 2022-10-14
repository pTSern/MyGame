#include "ShootBullet.h"
static SkillTypeRegister<ShootBulletSkill> s_register("SHOOTBULLET");
ShootBulletSkill::ShootBulletSkill() : SkillType()
{
}
void ShootBulletSkill::Update(float dt)
{
	this->g_pBulletManager->Running(dt);
}
void ShootBulletSkill::RunAction()
{
	this->g_pBulletManager->SetPlayerStatics(g_pPlayerStatics);
	this->g_pBulletManager->Call();
}
//void ShootBulletSkill::Init(Champion* pChampion, SkillStatics* pChampS, PlayerStatics* pPlayerStatics, int nBulletNum, std::string sPhysicType, std::string sBulletTexture, float fShootDelay )
//{
//	g_BulletStatic = new BulletStatic();
//	g_BulletStatic->Init(nBulletNum, sPhysicType, sBulletTexture, fShootDelay);
//	g_pPlayerStatics = pPlayerStatics;
//	this->g_pBulletManager = new BulletManager(pChampS, pPlayerStatics, g_BulletStatic, pChampion);
//}
void ShootBulletSkill::Init(BulletStatic* pBulletS, BulletElement* pBL, SkillStatics* pChampS, Champion* pChampion)
{
	//g_pPlayerStatics = pPlayerStatics;
	this->g_pBulletManager = new BulletManager(pBulletS, pBL, pChampS, pChampion);
}
void ShootBulletSkill::Cleaner()
{
	g_pBulletManager->Cleaner();
	CC_SAFE_DELETE(g_pBulletManager);
	//CC_SAFE_DELETE(g_BulletStatic);
	CC_SAFE_DELETE(g_pPlayerStatics);
}
bool ShootBulletSkill::IsFinish()
{
	return g_pBulletManager->IsFinish();
}