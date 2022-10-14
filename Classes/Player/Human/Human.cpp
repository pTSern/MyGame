#include "Human.h"

static PlayerRegister<Human> s_register("HUMAN");

Human::Human() : Player()
{
    this->g_pChampion = User::GetInstance()->GetSelectedChampion();
    this->g_pPlayerStatics->g_fAngle = this->g_pChampion->GetChampionStatics()->g_nMinAngle;

    this->g_pChampion->log();
    g_pInGameUI->Init(
        User::GetInstance()->GetUserUITexture()->g_sHPBar,
        User::GetInstance()->GetUserUITexture()->g_sSTMBar);
    g_pClientUI->Init(
        User::GetInstance()->GetUserUITexture()->g_sForceBar,
        User::GetInstance()->GetUserUITexture()->g_sBackground
    );

    m_LastSafePosition = this->g_pChampion->GetSprite()->getPosition();

    g_mChampionSkillList[SkillIndex::NORMAL_ATTACK] = ChampionSkillFactory::GetInstance()->Create(this->g_pChampion->g_mChampionSkillList[SkillIndex::NORMAL_ATTACK], this->g_pChampion, this->g_pPlayerStatics);
    //g_mChampionSkillList[SkillIndex::SKILL_1] = ChampionSkillFactory::GetInstance()->Create(this->g_pChampion->g_mChampionSkillList[SkillIndex::SKILL_1], this->g_pChampion, this->g_pPlayerStatics);
    //g_mChampionSkillList[SkillIndex::SKILL_2] = ChampionSkillFactory::GetInstance()->Create(this->g_pChampion->g_mChampionSkillList[SkillIndex::SKILL_2], this->g_pChampion, this->g_pPlayerStatics);
    //g_mChampionSkillList[SkillIndex::SUPPER_SKILL] = ChampionSkillFactory::GetInstance()->Create(this->g_pChampion->g_mChampionSkillList[SkillIndex::SUPPER_SKILL], this->g_pChampion, this->g_pPlayerStatics);

    if (this->g_pChampion->g_mChampionSkillList[SkillIndex::SUB_SKILL_1] != "NULL") g_mChampionSkillList[SkillIndex::SUB_SKILL_1] = ChampionSkillFactory::GetInstance()->Create(this->g_pChampion->g_mChampionSkillList[SkillIndex::SUB_SKILL_1], this->g_pChampion, this->g_pPlayerStatics);
    if (this->g_pChampion->g_mChampionSkillList[SkillIndex::SUB_SKILL_2] != "NULL") g_mChampionSkillList[SkillIndex::SUB_SKILL_2] = ChampionSkillFactory::GetInstance()->Create(this->g_pChampion->g_mChampionSkillList[SkillIndex::SUB_SKILL_2], this->g_pChampion, this->g_pPlayerStatics);

    
}
void Human::ClickEvent(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
    if (g_pPlayerAction->g_bIsTurn && g_pPlayerAction->g_eStatus != PlayerStatus::FALLING && !g_pPlayerAction->g_bIsShooting)
    {
        switch (keyCode)
        {
        case cocos2d::EventKeyboard::KeyCode::KEY_D:
            if (keyCode != cocos2d::EventKeyboard::KeyCode::KEY_A)
            {
                g_pPlayerStatics->g_eDir = RIGHT;
                g_pPlayerAction->g_bIsMoving = true;
            }
            break;
        case cocos2d::EventKeyboard::KeyCode::KEY_A:
            if (keyCode != cocos2d::EventKeyboard::KeyCode::KEY_D)
            {
                g_pPlayerStatics->g_eDir = LEFT;
                g_pPlayerAction->g_bIsMoving = true;
            }
            break;
        case cocos2d::EventKeyboard::KeyCode::KEY_1:
            break;
        case cocos2d::EventKeyboard::KeyCode::KEY_2:

            break;
        case cocos2d::EventKeyboard::KeyCode::KEY_P:
            break;
        case cocos2d::EventKeyboard::KeyCode::KEY_3:
            break;
        case cocos2d::EventKeyboard::KeyCode::KEY_W:
            g_pPlayerAction->g_bIsUpAngle = true;

            break;
        case cocos2d::EventKeyboard::KeyCode::KEY_S:
            g_pPlayerAction->g_bIsDownAngle = true;
            break;
        case cocos2d::EventKeyboard::KeyCode::KEY_SPACE:
            g_pPlayerAction->g_bIsForce = true;
            break;
        };
    }
}
void Human::PlayerIsTurnUpdate(float dt)
{
    this->PlayerMove(dt);
    this->UpdateAngle(dt);
    this->PlayerForcing(dt);

    Player::PlayerIsTurnUpdate(dt);
}
void Human::EndClickEvent(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
    if (g_pPlayerAction->g_bIsTurn && g_pPlayerAction->g_eStatus != PlayerStatus::FALLING && !g_pPlayerAction->g_bIsShooting)
    {
        switch (keyCode)
        {
        case cocos2d::EventKeyboard::KeyCode::KEY_1:
            break;
        case cocos2d::EventKeyboard::KeyCode::KEY_2:
            break;
        case cocos2d::EventKeyboard::KeyCode::KEY_P:
            this->Player::DoPassTurn();
            break;
        case cocos2d::EventKeyboard::KeyCode::KEY_3:
            
            break;
        case cocos2d::EventKeyboard::KeyCode::KEY_D:
            g_pPlayerAction->g_bIsMoving = false;
            break;
        case cocos2d::EventKeyboard::KeyCode::KEY_A:
            g_pPlayerAction->g_bIsMoving = false;
            
            break;
        case cocos2d::EventKeyboard::KeyCode::KEY_SPACE:
            g_pPlayerAction->g_bIsForce = false;

            g_pPlayerStatics->g_fForceMemory = g_pPlayerStatics->g_fForce;
            g_pPlayerStatics->g_fForce = 0;
            g_pPlayerAction->g_bIsShooting = true;
            g_nRunningSkillIndex = SkillIndex::NORMAL_ATTACK;
            g_mChampionSkillList[g_nRunningSkillIndex]->TriggerSkill();
            //this->Player::EndTurn();

            //g_fnSelector = std::bind(&Champion::NormalAtack, (g_pChampion), std::placeholders::_1);
            break;
        case cocos2d::EventKeyboard::KeyCode::KEY_W:
            g_pPlayerAction->g_bIsUpAngle = false;
            break;
        case cocos2d::EventKeyboard::KeyCode::KEY_S:
            g_pPlayerAction->g_bIsDownAngle = false;
            break;
        };
    }
}
void Human::Cleaner()
{
    Player::Cleaner();
}