#include "Normal_Attack.h"
#include "Skill/SkillType/ShootBullet/ShootBullet.h"
static ChampionSkillRegister<Hero_NormalAttack> s_register("HERO_NORMALATTACK");

Hero_NormalAttack::Hero_NormalAttack(Champion* pOwner, PlayerStatics* pPlayerStatics) : ChampionSkill(pOwner, pPlayerStatics)
{
	this->m_pSkill = SkillFactory::GetInstance()->Create("PASSIVE");
	this->m_pTriggerCondition = SkillConditionFactory::GetInstance()->Create("ONCLICK");
	this->m_pSkillType = SkillTypeFactory::GetInstance()->Create("SHOOTBULLET");
	cocos2d::log("     CONTRUCTOR HERO NORMAL ATTACK");
	this->Init();
}
void Hero_NormalAttack::Update(float dt)
{
	dynamic_cast<ShootBulletSkill*>(m_pSkillType)->Update(dt);
	this->m_pTriggerCondition->AutoCheckCondition();
	this->RecaculateSkill();
}

void Hero_NormalAttack::SkillMechanic()
{
	auto x = dynamic_cast<ShootBulletSkill*>(m_pSkillType);
	if (x)
	{
		x->RunAction();
		cocos2d::log("     RUN SKILL MECHANICCCC");
		cocos2d::log("<::::::::::::::::::::::::::::::::::::::::::::::::::::>");
	}
}
bool Hero_NormalAttack::CheckerTriggerCondition()
{
	if (this->m_pSkill->Checker_TriggerCondition(this->m_pCaster->GetChampionStatics()->g_nSkillPoint)
		&& this->m_pTriggerCondition->ConditionMatch())
	{
		return true;
	}
	return false;
}
void Hero_NormalAttack::RecaculateSkill()
{
	
}
void Hero_NormalAttack::Init()
{
	this->m_pSkill->Init("skill_icon/hero/normal_attack.png");
	this->m_pSkill->SetProperties
	(
		m_pCaster->GetStatics()->g_fATK,
		0,0,0,0,0,0,0,0,0,0,0
	);

	this->m_pTriggerCondition->Init(this->m_pCaster);

	auto x = dynamic_cast<ShootBulletSkill*>(m_pSkillType);
	if (x)
	{
		//x->Init(m_pCaster, m_pSkill->GetSkillStatics(), m_pPlayerStatics, 1, "DEFAULT", "bullet/hero/normal_attack.png", 0.5);
		auto pBulletStatic = new BulletStatic();
		pBulletStatic->Init(1, "DEFAULT", "bullet/hero/normal_attack.png", 0.5);

		BulletElement* pBL = new (std::nothrow) BulletElement();
		x->SetPlayerStatics(m_pPlayerStatics);
		x->Init(pBulletStatic, pBL, m_pSkill->GetSkillStatics(), m_pCaster);
	}
}
void Hero_NormalAttack::TriggerSkill()
{
	this->m_pTriggerCondition->CallCheckCondition();
	SoundManager::GetInstance()->PlaySoundEffect("audio/hero/normal_attack.mp3");
	if (CheckerTriggerCondition())
	{
		cocos2d::log("<::::::::::::::::::::::::::::::::::::::::::::::::::::>");
		cocos2d::log("     TRIGGED SKILLLLLLLLLLL");
		SkillMechanic();
	}
}
void Hero_NormalAttack::Cleaner()
{
	ChampionSkill::Cleaner();
	dynamic_cast<ShootBulletSkill*>(m_pSkillType)->Cleaner();
	CC_SAFE_DELETE(m_pSkillType);
}
bool Hero_NormalAttack::IsFinish()
{
	return m_pSkillType->IsFinish();
}