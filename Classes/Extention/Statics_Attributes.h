#pragma once
#include <string>
#include "cocos2d.h"

enum class TheAttribute
{
	STRENGTH = 0,
	AGILITY = 1,
	INTELLIGENCE = 2
};

enum class ChampionAction
{
	IDLE = 0,
	SHOOTING = 1,
	GET_HIT = 2,
	ATTACK = 3,
	CAST_SKILL = 4,
	DYING = 5,
	DEATH = 6
};
enum class SkillIndex
{
	NORMAL_ATTACK,
	SKILL_1,
	SKILL_2,
	SUPPER_SKILL,
	SUB_SKILL_1,
	SUB_SKILL_2
};

struct ChampionDoAction
{
public:
	ChampionAction g_Action;
	int g_nBulletNum;
	std::string g_sPhysicType, g_sBulletTexture;
	float g_fShootDelay;
public:
	
};

struct ChampionAttributes
{
public:
	ChampionAttributes(float _strength = 0, float _agility = 0, float _intelligence = 0)
	{
		g_fStrength = _strength;
		g_fAgility = _agility;
		g_fIntelligence = _intelligence;
	}

	//long getStrength() { return m_strength; };
	//long getAgility() { return m_agility; };
	//long getIntelligence() { return m_intelligence; };

	//void setStrength(long _strength) { m_strength = _strength; };
	//void setAgility(long _agility) { m_agility = _agility; };
	//void setIntelligence(long _intelligence) { m_intelligence = _intelligence; };

	float g_fStrength, g_fAgility, g_fIntelligence;
};

struct ChampionStatics
{
public:
	ChampionStatics(int ID = 0, TheAttribute mainATT = TheAttribute::STRENGTH, std::string name = "", int minAngle = 0, int maxAngle = 90, float maxForce = 100, float mass = 1, int LIFE = 0, float EXP = 0, int nSkillPoint = 1, std::string sFolderLocate = "", bool bIsIgnoreCollision = false)
	{

		g_nChampionID = ID;
		g_sName = name;

		g_nMinAngle = minAngle;
		g_nMaxAngle = maxAngle;
		g_fMaxForce = maxForce;
		

		g_fEXP = EXP;
		g_mainATT = mainATT;

		g_nSkillPoint = nSkillPoint;
		g_nLife = LIFE;
		g_fMass = mass;

		g_sFolderLocate = sFolderLocate;
		g_bIsIgnoreCollision = bIsIgnoreCollision;
	};

	std::string g_sName;
	std::string g_sFolderLocate;

	float g_fEXP;
	int g_nLevel;

	int g_nChampionID;
	int g_nMinAngle, g_nMaxAngle;
	float g_fMaxForce;
	float g_fMass;

	TheAttribute g_mainATT;
	int g_nSkillPoint;
	int g_nLife;

	bool g_bIsIgnoreCollision;
};
enum class ChampionSkillType
{
	PASSIVE = 0,
	RUN_ANIMATION = 1,
	SHOOT_BULLET = 2
};
struct SkillStatics 
{
public:
	std::string g_sName;
	float g_fPhysicDmg, g_fMagicDmg, g_fPureDmg;
	float g_fArmorPen, g_fMagicPen;
	int g_nCurrentCD, g_nCD;
	float g_fManaCost, g_fHpCost;
	float g_fPhysicCrit_Rate, g_fMagicCrit_Rate;
	float g_fPhysicCritDmg, g_fMagicCritDmg;
	std::string g_sDescription;
	bool g_bIsReady;
	int g_nSkillPoint;

};

struct Statics
{
public:
	Statics(float ATK = 0, float MAX_HP = 0, float Regen_HP = 0, float MAX_STAMINA = 0, float Regen_STM = 0, float ARMOR = 0 , float SP_Amp = 0, float SP_Res = 0
		, float SPD = 0, float fPsLifeSteal = 0, float fMgLifeSteal = 0)
	{
		g_fATK = ATK;
		g_fSP_Amp = SP_Amp;
		g_fARMOR = ARMOR;
		g_fSP_Res = SP_Res;
		g_fSPD = SPD;

		g_fPsLifeSteal = fPsLifeSteal;
		g_fMgLifeSteal = fMgLifeSteal;

		g_fHP = g_fMAX_HP = MAX_HP;
		g_fRegen_HP = Regen_HP;
		g_fCurrent_STM = g_fMAX_STAMINA = MAX_STAMINA;
		g_fRegen_STM = Regen_STM;
	};
	float g_fHP,g_fMAX_HP;
	float g_fRegen_HP;
	float g_fCurrent_STM, g_fMAX_STAMINA;
	float g_fRegen_STM;
	float g_fATK, g_fSP_Amp;
	float g_fARMOR, g_fSP_Res;
	float g_fSPD;
	float g_fPsLifeSteal, g_fMgLifeSteal;
};

enum DIR
{
	LEFT = -1,
	RIGHT = 1
};

