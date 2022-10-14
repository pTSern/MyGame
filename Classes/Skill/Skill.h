#pragma once
#include "cocos2d.h"
#include "Extention/Statics_Attributes.h"
class Skill : public cocos2d::Node
{
public:
	void Init(std::string sTexture)
	{
		m_pSkillStatics = new SkillStatics();
		m_pSkillStatics->g_bIsReady = false;
		this->m_pIcon = cocos2d::Sprite::create(sTexture);
		this->addChild(m_pIcon);
	}
public:
	virtual void Cleaner()
	{
		m_pIcon->release();
		//CC_SAFE_DELETE(m_pIcon);
		CC_SAFE_DELETE(m_pSkillStatics);
	}
public:
	bool Checker_TriggerCondition(float fCurrentMana, int nCurrentSkillPoint, float fCurrentHp)
	{
		if (nCurrentSkillPoint >= this->m_pSkillStatics->g_nSkillPoint)
		{
			if (fCurrentMana >= this->m_pSkillStatics->g_fManaCost)
			{
				if (fCurrentHp >= this->m_pSkillStatics->g_fHpCost)
				{
					return true;
				}
			}
		}
		return false;
	}
	bool Checker_TriggerCondition(float fCurrentMana, int nCurrentSkillPoint)
	{
		if (nCurrentSkillPoint >= this->m_pSkillStatics->g_nSkillPoint)
		{
			if (fCurrentMana >= this->m_pSkillStatics->g_fManaCost)
			{
				return true;
				
			}
		}
		return false;
	}
	bool Checker_TriggerCondition(int nCurrentSkillPoint, float fCurrentHp)
	{
		if (nCurrentSkillPoint >= this->m_pSkillStatics->g_nSkillPoint)
	{
			if (fCurrentHp >= this->m_pSkillStatics->g_fHpCost)
			{
				return true;
			}
		}
		return false;
	}
	bool Checker_TriggerCondition(int nCurrentSkillPoint)
	{
		if (nCurrentSkillPoint >= this->m_pSkillStatics->g_nSkillPoint)
		{
			return true;
		}
		return false;
	}
	bool Checker_TriggerCondition(float fCurrentMana, float fCurrentHp)
	{
		if (fCurrentMana >= this->m_pSkillStatics->g_fManaCost)
		{
			if (fCurrentHp >= this->m_pSkillStatics->g_fHpCost)
			{
				return true;
			}
		}

		return false;
	}

public:
	inline void SetIconPosition(cocos2d::Point pos)
	{
		this->m_pIcon->setPosition(pos);
	}
	inline void SetName(std::string name)
	{
		m_pSkillStatics->g_sName = name;
	}
	inline void SetCooldown(int CD)
	{
		m_pSkillStatics->g_nCurrentCD = m_pSkillStatics->g_nCD = CD;
	}
	inline void SetSkillLogic(std::function<void(float dt)> fnLogic)
	{
		this->m_fnSelector = fnLogic;
	}
	inline void SetDescription(std::string description)
	{
		m_pSkillStatics->g_sDescription = description;
	}
	void SetProperties(float physicDmg = 0, float magicDmg = 0, float pureDmg = 0, float armorPen = 0, float magicPen = 0, float manaCost = 0, float hpCost = 0,
		float fPhysicCritDmg = 0, float fMagicCrit_Rate = 0, float physicCritDmg = 0, float magicCritDmg = 0, int nSkillPoint = 0)
	{
		m_pSkillStatics->g_nSkillPoint = nSkillPoint;

		m_pSkillStatics->g_fPhysicDmg = physicDmg;
		m_pSkillStatics->g_fMagicDmg = magicDmg;
		m_pSkillStatics->g_fPureDmg = pureDmg;

		m_pSkillStatics->g_fArmorPen = armorPen;
		m_pSkillStatics->g_fMagicPen = magicPen;

		m_pSkillStatics->g_fManaCost = manaCost;
		m_pSkillStatics->g_fHpCost = hpCost;

		m_pSkillStatics->g_fPhysicCrit_Rate = fPhysicCritDmg;
		m_pSkillStatics->g_fMagicCrit_Rate = fMagicCrit_Rate;

		m_pSkillStatics->g_fPhysicCritDmg = physicCritDmg;
		m_pSkillStatics->g_fMagicCritDmg = magicCritDmg;
	}
	void RefreshSkill()
	{
		m_pSkillStatics->g_nCurrentCD = m_pSkillStatics->g_nCD;
		m_pSkillStatics->g_bIsReady = true;
	}
	void TriggedSkill()
	{
		m_pSkillStatics->g_bIsReady = false;
		m_pSkillStatics->g_nCurrentCD = m_pSkillStatics->g_nCD;
	}
	void AutoCooldown()
	{
		//if skill is not ready, auto reduce cooldown (this happen when a round passed and player[champion] got no debuff that stop coodown)
		if (!m_pSkillStatics->g_bIsReady) m_pSkillStatics->g_nCurrentCD--;

		//if curren cooldown is = 0 or < 0, set the skill is ready.
		if (m_pSkillStatics->g_nCurrentCD <= 0) m_pSkillStatics->g_bIsReady = true;
	}
	inline SkillStatics* GetSkillStatics()
	{
		return this->m_pSkillStatics;
	}

protected:
	std::function<void(float dt)> m_fnSelector;
	cocos2d::Sprite* m_pIcon;

	SkillStatics* m_pSkillStatics;

	std::string m_sType;
};