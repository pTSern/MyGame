#include "Champion.h"

Champion::Champion(const XProperties* pProperties) : GameObject(pProperties)
{
	m_pChampionAttributes = new (std::nothrow) ChampionAttributes();
	m_pChampionAttributes_LvIncrease = new (std::nothrow) ChampionAttributes();
	m_pChampionStatics = new (std::nothrow) ChampionStatics();
	m_pStatics = new (std::nothrow) Statics();
	this->SetChampionAction(ChampionAction::IDLE);
	g_mChampionTexture[ChampionAction::DEATH] = "champion/death.png";

	this->SetContestBitMark(Node_StringNTag::PlayerContactBitmask());
	m_pSprite->setTag(2);
}

void Champion::ConvertAdditionAttributesToStatic(ChampionAttributes* pChampionAttributes)
{
	Convert_Strength_to_STT(pChampionAttributes);
	Convert_Agility_to_STT(pChampionAttributes);
	Convert_Intelligence_to_STT(pChampionAttributes);
}
void Champion::Update(float dt)
{
	//this->m_pSprite->runAction(cocos2d::MoveBy::create(0, cocos2d::Point(this->m_pStatics->g_fSPD/100, 0)));
	GameObject::Update(dt);
	//Check current Hp and current Stamina if it over max values
	this->ValidStatics();

	//Check champion if he death, dying or not
	this->LifeCheck(dt);

	//Alway recaculate attributes to status
	//this->Convert_ATT_to_STT();
}
void Champion::GravityEffect(float gracityAcc, float dt)
{
	this->m_pSprite->runAction(cocos2d::MoveBy::create(dt, cocos2d::Point(0, this->m_pChampionStatics->g_fMass * gracityAcc)));
	//this->SetPosition(cocos2d::Point(this->m_pSprite->getPosition().x , this->m_pSprite->getPosition().y + this->m_pChampionStatics->g_fMass * gracityAcc));
}
void Champion::SuddenDeath()
{
	this->m_pChampionStatics->g_nLife = 0;
	this->m_pStatics->g_fHP = 0;
}
void Champion::VoidDetect()
{
	this->SuddenDeath();
}
void Champion::Init()
{
	this->Convert_ATT_to_STT();
	//this->FirstSetSTT();
}
void Champion::SetFlip(DIR edir)
{
	if (edir == RIGHT) m_pSprite->setFlippedX(true);
	if (edir == LEFT) m_pSprite->setFlippedX(false);
		
}
void Champion::CalculateChampionAttributes()
{
	this->m_pChampionAttributes = this->m_pChampionAttributes_Base;
	
	m_pChampionAttributes->g_fStrength += m_pChampionAttributes_LvIncrease->g_fStrength * m_pChampionStatics->g_nLevel;
	m_pChampionAttributes->g_fAgility += m_pChampionAttributes_LvIncrease->g_fAgility * m_pChampionStatics->g_nLevel;
	m_pChampionAttributes->g_fIntelligence += m_pChampionAttributes_LvIncrease->g_fIntelligence * m_pChampionStatics->g_nLevel;

	for (int i = 0; i < m_vEquipedWeaponList.size(); i++)
	{
		m_pChampionAttributes->g_fStrength += m_vEquipedWeaponList[i]->GetChampionAttributes()->g_fStrength;
		m_pChampionAttributes->g_fAgility += m_vEquipedWeaponList[i]->GetChampionAttributes()->g_fAgility;
		m_pChampionAttributes->g_fIntelligence += m_vEquipedWeaponList[i]->GetChampionAttributes()->g_fIntelligence;
	}

}
void Champion::AutoLevel()
{
	this->m_pChampionStatics->g_nLevel = this->m_pChampionStatics->g_fEXP / 1000;
}

void Champion::CalculateStatics()
{
	m_pStatics = m_pStatics_Base;
	for (int i = 0; i < m_vEquipedWeaponList.size(); i++)
	{
		m_pStatics->g_fATK += m_vEquipedWeaponList[i]->GetStatics()->g_fATK;
		m_pStatics->g_fRegen_HP += m_vEquipedWeaponList[i]->GetStatics()->g_fRegen_HP;
		m_pStatics->g_fCurrent_STM = m_pStatics->g_fMAX_STAMINA += m_vEquipedWeaponList[i]->GetStatics()->g_fMAX_STAMINA;
		m_pStatics->g_fHP = m_pStatics->g_fMAX_HP += m_vEquipedWeaponList[i]->GetStatics()->g_fMAX_HP;
		m_pStatics->g_fRegen_STM += m_vEquipedWeaponList[i]->GetStatics()->g_fRegen_STM;
		m_pStatics->g_fSP_Amp += m_vEquipedWeaponList[i]->GetStatics()->g_fSP_Amp;
		m_pStatics->g_fARMOR += m_vEquipedWeaponList[i]->GetStatics()->g_fARMOR;
		m_pStatics->g_fSP_Res += m_vEquipedWeaponList[i]->GetStatics()->g_fSP_Res;
		m_pStatics->g_fSPD += m_vEquipedWeaponList[i]->GetStatics()->g_fSPD;

	}
}

void Champion::FirstSetSTT()
{
	this->m_pStatics->g_fCurrent_STM = this->m_pStatics->g_fMAX_STAMINA;
	this->m_pStatics->g_fHP = this->m_pStatics->g_fMAX_HP;
}

void Champion::Convert_ATT_to_STT()
{
	AutoLevel();

	CalculateChampionAttributes();
	CalculateStatics();

	Convert_Strength_to_STT(m_pChampionAttributes);
	Convert_Agility_to_STT(m_pChampionAttributes);
	Convert_Intelligence_to_STT(m_pChampionAttributes);

}

void Champion::Convert_Strength_to_STT(ChampionAttributes* pChampionAttributes)
{
	m_pStatics->g_fHP = m_pStatics->g_fMAX_HP += pChampionAttributes->g_fStrength * 5;
	m_pStatics->g_fRegen_HP += pChampionAttributes->g_fStrength * 1;
	float x = pChampionAttributes->g_fStrength;
	if (m_pChampionStatics->g_mainATT == TheAttribute::STRENGTH) m_pStatics->g_fATK += x;

}

void Champion::Convert_Agility_to_STT(ChampionAttributes* pChampionAttributes)
{
	m_pStatics->g_fSPD += pChampionAttributes->g_fAgility * 0.01;
	m_pStatics->g_fARMOR += pChampionAttributes->g_fAgility * 1/6;
	float x = pChampionAttributes->g_fAgility;
	if (m_pChampionStatics->g_mainATT == TheAttribute::AGILITY) m_pStatics->g_fATK += x;
}

void Champion::Convert_Intelligence_to_STT(ChampionAttributes* pChampionAttributes)
{
	m_pStatics->g_fCurrent_STM = m_pStatics->g_fMAX_STAMINA += pChampionAttributes->g_fIntelligence * 2;
	m_pStatics->g_fRegen_STM += pChampionAttributes->g_fIntelligence * 0.2;
	float x = pChampionAttributes->g_fIntelligence;
	if (m_pChampionStatics->g_mainATT == TheAttribute::INTELLIGENCE) m_pStatics->g_fATK += x;
}
void Champion::Cleaner()
{
	CC_SAFE_DELETE(m_pChampionAttributes);
	CC_SAFE_DELETE(m_pStatics);
	CC_SAFE_DELETE(m_pChampionAttributes_Base);
	CC_SAFE_DELETE(m_pChampionAttributes_LvIncrease);
	CC_SAFE_DELETE(m_pChampionAttributes_LvIncrease);
	CC_SAFE_DELETE(m_pStatics_Base);
	CC_SAFE_DELETE(m_pChampionEconomy);
	
	for (auto& x : m_vEquipedWeaponList)
	{
		x.second->Cleaner();
	}
	for (auto& x : m_vEquipedWeaponList)
	{
		CC_SAFE_DELETE(x.second);
	}

	//GameObject::Cleaner();
}
void Champion::DoPassTurn()
{

}
void Champion::GetHit(SkillStatics* pSkill)
{
	float DmgRecive_P = pSkill->g_fPhysicDmg * (1 - (0.06 * (this->m_pStatics->g_fARMOR - pSkill->g_fArmorPen) / (1 + (0.06 * (abs(this->m_pStatics->g_fARMOR - pSkill->g_fArmorPen))))));
	this->m_pStatics->g_fHP -= DmgRecive_P;

	float DmgRecive_M = (pSkill->g_fMagicDmg + pSkill->g_fMagicDmg * (pSkill->g_fMagicPen / 100)) * (1 - (this->m_pStatics->g_fSP_Res / 100));
	this->m_pStatics->g_fHP -= DmgRecive_M;

	//Change champion's action to GET_HIT when champion calls this function
	this->SetChampionAction(ChampionAction::GET_HIT);
	//this->LifeCheck(0);
}
void Champion::log() 
{
	cocos2d::log(("\n" + this->GetSText()).c_str());
	cocos2d::log(("ATK: " + std::to_string(m_pStatics->g_fATK)).c_str());
	cocos2d::log(("HP/MAX HP: " + std::to_string(m_pStatics->g_fHP) + "/" + std::to_string(m_pStatics->g_fMAX_HP)).c_str());
	cocos2d::log(("STAMINA/MAX STAMINA: " + std::to_string(m_pStatics->g_fCurrent_STM) + "/" + std::to_string(m_pStatics->g_fMAX_STAMINA)).c_str());
	cocos2d::log(("Regen HP: " + std::to_string(m_pStatics->g_fRegen_HP)).c_str());
	cocos2d::log(("Regen STAMINA: " + std::to_string(m_pStatics->g_fRegen_STM)).c_str());
	cocos2d::log(("SPELL AMP: " + std::to_string(m_pStatics->g_fSP_Amp)).c_str());
	cocos2d::log(("ARMOR: " + std::to_string(m_pStatics->g_fARMOR)).c_str());
	cocos2d::log(("SPELL RES: " + std::to_string(m_pStatics->g_fSP_Res)).c_str());
	cocos2d::log(("SPEED: " + std::to_string(m_pStatics->g_fSPD)).c_str());
	cocos2d::log(("LV: " + std::to_string(this->m_pChampionStatics->g_nLevel)).c_str());
	cocos2d::log(("Pos: " + std::to_string(this->m_pSprite->getPosition().x) + " - " + std::to_string(this->m_pSprite->getPosition().y)).c_str());
	cocos2d::log(("AGI: " + std::to_string(m_pChampionAttributes->g_fAgility)).c_str());
	cocos2d::log(("STR: " + std::to_string(m_pChampionAttributes->g_fStrength)).c_str());
	cocos2d::log(("INT: " + std::to_string(m_pChampionAttributes->g_fIntelligence)).c_str());
}
int Champion::GetChampionMainAttributes()
{
	if (m_pChampionStatics->g_mainATT == TheAttribute::STRENGTH) return m_pChampionAttributes->g_fStrength;
	if (m_pChampionStatics->g_mainATT == TheAttribute::AGILITY) return m_pChampionAttributes->g_fAgility;
	if (m_pChampionStatics->g_mainATT == TheAttribute::INTELLIGENCE) return m_pChampionAttributes->g_fIntelligence;
}
void Champion::Move(DIR eDir, float dt) 
{
	this->SetFlip(eDir);
	//Only move when champion have enough stamina ( > 0)
	if ((int)this->m_pStatics->g_fCurrent_STM > 0)
	{
		this->m_pSprite->runAction(cocos2d::MoveBy::create(dt, cocos2d::Point(this->m_pStatics->g_fSPD * 5 * (int)eDir, 0)));
		//Moving lose stamina => Decrease stamina every move
		this->m_pStatics->g_fCurrent_STM -= 0.02*1 ;
		//cocos2d::log((std::to_string(this->m_pSprite->getPosition().x) + " - " + std::to_string(this->m_pSprite->getPosition().y)).c_str());
	}

	
	//cocos2d::log((std::to_string((int)this->m_pStatics->g_fCurrent_STM)).c_str());
}

//Return true if champion is really dead (have no life left)
void Champion::LifeCheck(float dt)
{
	//Champion is death because he have no current hp
	if (this->m_pStatics->g_fHP <= 0)
	{
		//Set champion's action to death. 
		this->SetChampionAction(ChampionAction::DYING);
		cocos2d::log("DYINGGGGGG");
		//Check champion current life
		if (this->m_pChampionStatics->g_nLife <= 0)
		{
			//This mean champion is really dead
			//Set sprite texture to death texture
			this->SetChampionAction(ChampionAction::DEATH);
			this->m_pSprite->setTexture(g_mChampionTexture[this->m_eChampionAction]);
			cocos2d::log("DEATH");
		}
		else
		{
			//Call respawn func to spawn champion
			this->Respawn(dt);
			cocos2d::log("RESPAWNING");
		}
	}
	//switch (GetChampionAction())
	//{
	//case ChampionAction::DYING:
	//	cocos2d::log("DYING");
	//	break;
	//case ChampionAction::DEATH:
	//	cocos2d::log("DEATH");
	//	break;
	//case ChampionAction::IDLE:
	//	cocos2d::log("DILE");
	//	break;
	//}
}
void Champion::Respawn(float dt)
{
	//Reduce champion's life
	this->m_pChampionStatics->g_nLife--;
	//Respawn with 100% HP
	this->m_pStatics->g_fHP = this->m_pStatics->g_fMAX_HP;
	//Set champion action to idle
	this->SetChampionAction(ChampionAction::IDLE);
	cocos2d::log("RESPAWN SUCCESS");
}
void Champion::EndTurn()
{

}
void Champion::ValidStatics()
{
	if (this->m_pStatics->g_fHP > this->m_pStatics->g_fMAX_HP) this->m_pStatics->g_fHP = this->m_pStatics->g_fMAX_HP;
	if (this->m_pStatics->g_fCurrent_STM > this->m_pStatics->g_fMAX_STAMINA) this->m_pStatics->g_fCurrent_STM = this->m_pStatics->g_fMAX_STAMINA;
}