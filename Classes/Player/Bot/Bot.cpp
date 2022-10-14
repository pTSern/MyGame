#include "Bot.h"

static PlayerRegister<Bot> s_register("BOT");
Bot::Bot() : Player()
{
	XProperties* pPro = new XProperties("champion/hero.png", new cocos2d::Point(500, 250), 0, true);
	GameObject* pGO = GameObjectFactory::GetInstance()->Create("Hero", pPro);

	p_pAIBrain = BotFactory::GetInstance()->Create("HERO");

	this->g_pChampion = dynamic_cast<Champion*>(pGO);
	g_pInGameUI->Init("ui/hp_bar/default.png", "ui/stamina_bar/default.png");
	g_pClientUI->Init("ui/force_bar/default.png", "ui/background/default.png");
	g_pChampion->SetBaseChampionAttributes(User::GetInstance()->GetSelectedChampion()->GetChampionAttributes());
	float supper = User::GetInstance()->GetUserWinRate() - 0.5;

	cocos2d::log(("SUPPER CONST: " + std::to_string(supper)).c_str());
	Statics* pBaseS = new Statics();
	
	pBaseS->g_fATK += (supper * User::GetInstance()->GetSelectedChampion()->GetStatics()->g_fATK + (int) (1 + supper) * User::GetInstance()->GetSelectedChampion()->GetChampionMainAttributes());
	pBaseS->g_fRegen_HP += (supper * User::GetInstance()->GetSelectedChampion()->GetStatics()->g_fRegen_HP);
	pBaseS->g_fMAX_STAMINA += (supper * User::GetInstance()->GetSelectedChampion()->GetStatics()->g_fMAX_STAMINA);
	pBaseS->g_fRegen_STM += (supper * User::GetInstance()->GetSelectedChampion()->GetStatics()->g_fRegen_STM);
	pBaseS->g_fSP_Amp += (supper * User::GetInstance()->GetSelectedChampion()->GetStatics()->g_fSP_Amp + User::GetInstance()->GetSelectedChampion()->GetStatics()->g_fSP_Amp);
	pBaseS->g_fARMOR += (supper * User::GetInstance()->GetSelectedChampion()->GetStatics()->g_fARMOR);
	pBaseS->g_fSP_Res += (supper * User::GetInstance()->GetSelectedChampion()->GetStatics()->g_fSP_Res);
	pBaseS->g_fSPD += (supper * User::GetInstance()->GetSelectedChampion()->GetStatics()->g_fSPD);

	g_pChampion->SetTheStatics(pBaseS);
	g_pChampion->Init();

	ChampionStatics* pCS = new ChampionStatics(0, TheAttribute::STRENGTH, "HERO", 45, 90, 100, 1, 0);

	g_pChampion->SetChampionStatics(pCS);

	g_mChampionSkillList[SkillIndex::NORMAL_ATTACK] = ChampionSkillFactory::GetInstance()->Create(this->g_pChampion->g_mChampionSkillList[SkillIndex::NORMAL_ATTACK], this->g_pChampion, this->g_pPlayerStatics);
	//g_mChampionSkillList[SkillIndex::SKILL_1] = ChampionSkillFactory::GetInstance()->Create(this->g_pChampion->g_mChampionSkillList[SkillIndex::SKILL_1], this->g_pChampion, this->g_pPlayerStatics);
	//g_mChampionSkillList[SkillIndex::SKILL_2] = ChampionSkillFactory::GetInstance()->Create(this->g_pChampion->g_mChampionSkillList[SkillIndex::SKILL_2], this->g_pChampion, this->g_pPlayerStatics);
	//g_mChampionSkillList[SkillIndex::SUPPER_SKILL] = ChampionSkillFactory::GetInstance()->Create(this->g_pChampion->g_mChampionSkillList[SkillIndex::SUPPER_SKILL], this->g_pChampion, this->g_pPlayerStatics);

	if (this->g_pChampion->g_mChampionSkillList[SkillIndex::SUB_SKILL_1] != "NULL") g_mChampionSkillList[SkillIndex::SUB_SKILL_1] = ChampionSkillFactory::GetInstance()->Create(this->g_pChampion->g_mChampionSkillList[SkillIndex::SUB_SKILL_1], this->g_pChampion, this->g_pPlayerStatics);
	if (this->g_pChampion->g_mChampionSkillList[SkillIndex::SUB_SKILL_2] != "NULL") g_mChampionSkillList[SkillIndex::SUB_SKILL_2] = ChampionSkillFactory::GetInstance()->Create(this->g_pChampion->g_mChampionSkillList[SkillIndex::SUB_SKILL_2], this->g_pChampion, this->g_pPlayerStatics);

	cocos2d::log("BOT CONTRUCTOR");
}
void Bot::ClickEvent(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
	cocos2d::log("BOT CLICk");
}
void Bot::EndClickEvent(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event * event)
{
	//this->g_pPlayerStatics->g_eDir = (DIR)(-1 * (int)BattleElement::GetInstance()->Cheat_GetPlayerDir());

}
void Bot::Cleaner()
{
	Player::Cleaner();
}

void Bot::AutoSetDir()
{
	if (GetPosition().x > BattleElement::GetInstance()->Cheat_GetPlayerPos().x) this->g_pPlayerStatics->g_eDir = LEFT;
	else this->g_pPlayerStatics->g_eDir = RIGHT;

	this->g_pChampion->Move(this->g_pPlayerStatics->g_eDir, 0);
}
void Bot::AutoMove()
{

}
void Bot::AutoForce()
{
	cocos2d::log("     AI FORCE CALCULATING");
	g_pPlayerStatics->g_fForce = p_pAIBrain->ForceCalculate(this->g_pPlayerStatics->g_eDir, this->g_pPlayerStatics->g_fAngle*PI / 180, 1, BattleElement::GetInstance()->Cheat_GetPlayerPos(), this->GetPosition(), this->g_pChampion->GetChampionStatics()->g_fMaxForce);
	switch ((ErorDetect)g_pPlayerStatics->g_fForce)
	{
	case ErorDetect::OUT_OF_FORCE:
		cocos2d::log("          OUT OF FORCE");
		AutoAngle(AI_Angle::DOWN);
		AutoForce();
		break;
	case ErorDetect::INVALID_TIME:
		cocos2d::log("          INVALID_TIME");
		if(this->g_pPlayerStatics->g_fAngle >= this->g_pChampion->GetChampionStatics()->g_nMaxAngle)
			AutoAngle(AI_Angle::DOWN);
		else AutoAngle(AI_Angle::UP);
		AutoForce();
		break;
	case ErorDetect::INVALID_DELTA:
		cocos2d::log("          INVALID_DELTA");
		if (this->g_pPlayerStatics->g_fAngle >= this->g_pChampion->GetChampionStatics()->g_nMaxAngle)
			AutoAngle(AI_Angle::DOWN);
		else AutoAngle(AI_Angle::UP);
		AutoForce();
		break;
	case ErorDetect::OUT_OF_MAP:
		cocos2d::log("          OUT OF MAP");
		AutoAngle(AI_Angle::DOWN);
		AutoForce();
	default:
		break;
	}
}
void Bot::AutoSkill()
{

}
void Bot::AutoAngle(AI_Angle aia)
{
	if (aia == AI_Angle::DEFAULT) this->g_pPlayerStatics->g_fAngle = 90;
	if (aia == AI_Angle::DOWN) this->g_pPlayerStatics->g_fAngle -= 1;
	if (aia == AI_Angle::UP) this->g_pPlayerStatics->g_fAngle += 1;

}
void Bot::PlayerIsTurnUpdate(float dt)
{
	
	if (!this->g_pPlayerAction->g_bIsShooting && g_pPlayerAction->g_eStatus != PlayerStatus::FALLING && BattleElement::GetInstance()->Cheat_GetPlayerStatus() != PlayerStatus::FALLING)
	{
		cocos2d::log("**************************************************");
		AutoSetDir();
		AutoAngle(AI_Angle::DEFAULT);
		AutoForce();

		g_pPlayerStatics->g_fForceMemory = g_pPlayerStatics->g_fForce;
		g_pPlayerAction->g_bIsShooting = true;
		g_nRunningSkillIndex = SkillIndex::NORMAL_ATTACK;
		g_mChampionSkillList[g_nRunningSkillIndex]->TriggerSkill();
		g_pPlayerStatics->g_fForce = 0;
		cocos2d::log(("     AI Force: " + std::to_string(g_pPlayerStatics->g_fForceMemory) + " AI Angle: " + std::to_string(g_pPlayerStatics->g_fAngle)).c_str());
		cocos2d::log(("     BOT POS: " + std::to_string(GetPosition().x) + " - " + std::to_string(GetPosition().y)).c_str());
		this->g_pPlayerAction->g_bIsShooting = true;
		cocos2d::log("**************************************************");
	}
	Player::PlayerIsTurnUpdate(dt);
}