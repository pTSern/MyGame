#include "Hero.h"
static Register<Hero> s_register("Hero");

Hero::Hero(const XProperties* pProperties) : Champion(pProperties)
{
	g_mChampionSkillList[SkillIndex::NORMAL_ATTACK] = "HERO_NORMALATTACK";
	//g_mChampionSkillList[SkillIndex::SKILL_1] = "";
	//g_mChampionSkillList[SkillIndex::SKILL_2] = "";
	//g_mChampionSkillList[SkillIndex::SUPPER_SKILL] = "";
	g_mChampionSkillList[SkillIndex::SUB_SKILL_1] = "NULL";
	g_mChampionSkillList[SkillIndex::SUB_SKILL_2] = "NULL";
}
void Hero::Update(float dt)
{
	Champion::Update(dt);
}
void Hero::VoidDetect()
{
	Champion::VoidDetect();
}
void Hero::GetHit(SkillStatics* pSkill)
{
	cocos2d::log("GET HITTTTTTTTTTTTTTTTTTTTT");
	Champion::GetHit(pSkill);
}
void Hero::Move(DIR edir, float dt)
{
	Champion::Move(edir, dt);
}
void Hero::DoPassTurn()
{
	this->m_pStatics->g_fHP += GetStatics()->g_fRegen_HP;
	this->m_pStatics->g_fCurrent_STM += GetStatics()->g_fRegen_STM * 0.7;
}
void Hero::Respawn(float dt)
{
	Champion::Respawn(dt);
}

void Hero::EndTurn()
{
	this->m_pStatics->g_fCurrent_STM += GetStatics()->g_fRegen_STM * 0.3;
}
void Hero::Cleaner()
{
	Champion::Cleaner();
}