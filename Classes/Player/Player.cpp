#include "Player.h"

cocos2d::EventListenerKeyboard* Player::m_pListenerKeyboard = cocos2d::EventListenerKeyboard::create();

Player::Player()
{
    g_pPlayerAction = new PlayerAction();
    g_pPlayerStatics = new PlayerStatics();
    g_pInGameUI = new InGameUI();
    g_pClientUI = new PlayerClientUI();
}
cocos2d::EventListenerKeyboard* Player::GetKeyboardListener()
{
	return this->m_pListenerKeyboard;
}
void Player::PlayerUpdate(float dt)
{
    
}
void Player::PlayerUIUpdate()
{
    this->g_pInGameUI->Set_HPSTM_BarPosition(cocos2d::Point(this->GetPosition().x, this->GetPosition().y - this->GetContentSize().height / 1.5));
    this->g_pInGameUI->Display_HP_Bar(this->g_pChampion->GetStatics()->g_fHP, this->g_pChampion->GetStatics()->g_fMAX_HP);
    this->g_pInGameUI->Display_STM_Bar(this->g_pChampion->GetStatics()->g_fCurrent_STM, this->g_pChampion->GetStatics()->g_fMAX_STAMINA);

    this->g_pClientUI->Set_AngleVector_Position(GetPosition());
    this->g_pClientUI->Set_Angle_Rotation(this->g_pPlayerStatics->g_fAngle, g_pPlayerStatics->g_eDir);
}
void Player::PlayerAliveUpdate(float dt)
{
    this->g_pChampion->Update(dt);
    if (!LifeCheck(dt)) this->PlayerDeadUpdate(dt);

    this->GravityEffect(dt);
    this->VoidDetect();
    this->PlayerUIUpdate();
}
void Player::PlayerDeadUpdate(float dt)
{
    cocos2d::log("DEAD UPDATE");
    this->g_pInGameUI->Disable();
    //this->g_pClientUI->Disable();
}
void Player::DoPassTurn()
{
    this->g_pChampion->DoPassTurn();
    this->EndTurn();
}
void Player::PlayerIsTurnUpdate(float dt)
{
    //cocos2d::log("PLAYER IS TURN UPDATETING");
    
    if (g_pPlayerAction->g_bIsShooting) CastingSkill(dt);

    for (auto& x : g_mChampionSkillList) x.second->Update(dt);

    if (g_pPlayerAction->g_eStatus == PlayerStatus::FALLING)
    {
        g_pPlayerAction->g_bIsMoving = false;
        g_pPlayerAction->g_bIsForce = false;
    }
}
void Player::PlayerMove(float dt)
{
    //cocos2d::log( ( "MOVE INT: " + std::to_string((int)(g_pPlayerAction->g_bIsMoving) * this->g_pPlayerStatics->g_eDir)).c_str());
    if (g_pPlayerAction->g_bIsMoving)
    {
        this->g_pChampion->Move(this->g_pPlayerStatics->g_eDir, dt);
        //cocos2d::log("PLAYER MOVING");
    }
    if (MapManager::GetInstance()->CheckMapCollision(cocos2d::Point(this->GetPosition().x + (int)this->g_pPlayerStatics->g_eDir * this->GetContentSize().width / 2, this->GetPosition().y), GetContentSize())
        || MapManager::GetInstance()->IsReachSideMap(GetPosition(), GetContentSize()))
    {
        this->SetPositionToLastSafe();
        //cocos2d::log("SET LAST SAFE");
        g_pPlayerAction->g_bIsMoving = false;
    }
    else m_LastSafePosition = this->GetPosition();
    
    //cocos2d::log((std::to_string(this->GetPosition().x) + " - " + std::to_string(this->GetPosition().y)).c_str());
}

///
/// Check if player can start a new turn 
/// 
/// @return true if player is available, false if player is not available
bool Player::IsValidTurn()
{
    if (this->g_pPlayerAction->g_bIsEndTurn) return false;
    if (!LifeCheck(0)) return false;
    return true;
}
void Player::UpdateAngle(float dt)
{
    if (this->g_pPlayerAction->g_bIsUpAngle && this->g_pPlayerStatics->g_fAngle < this->g_pChampion->GetChampionStatics()->g_nMaxAngle) this->g_pPlayerStatics->g_fAngle++;
    if (this->g_pPlayerAction->g_bIsDownAngle && this->g_pPlayerStatics->g_fAngle > this->g_pChampion->GetChampionStatics()->g_nMinAngle) this->g_pPlayerStatics->g_fAngle--;
}

/// 
/// Check if player is die or not
/// 
/// @param dt: no need to understand
/// 
/// @return true if player is still alive, false if player is dead
bool Player::LifeCheck(float dt)
{
    if (this->g_pChampion->GetChampionAction() == ChampionAction::DEATH)
        return false;
    return true;
}
void Player::StartTurn()
{
    this->g_pPlayerAction->g_bIsTurn = true;
    this->g_pPlayerAction->g_bIsEndTurn = true;
    this->g_pPlayerAction->g_eStatus = PlayerStatus::IS_TURN;
}
void Player::EndTurn()
{
    this->g_pPlayerAction->g_bIsTurn = false;
    this->g_pPlayerAction->g_bIsEndTurn = false;
    this->g_pPlayerAction->g_eStatus = PlayerStatus::END_TURN;

    g_pPlayerAction->g_bIsMoving = false;
    g_pPlayerAction->g_bIsForce = false;
    g_pPlayerStatics->g_bIsReverse = false;

    this->g_pChampion->EndTurn();
}
void Player::SetPositionToLastSafe()
{
    this->g_pChampion->SetPosition(m_LastSafePosition);
    cocos2d::log("BACK TO SAFE POINT");
}
void Player::SetPosition(cocos2d::Point pos)
{
    this->g_pChampion->SetPosition(pos);
}
cocos2d::Point Player::GetPosition()
{
    return this->g_pChampion->GetSprite()->getPosition();
}
cocos2d::Size Player::GetContentSize()
{
    return this->g_pChampion->GetSprite()->getContentSize();
}
void Player::GravityEffect(float dt)
{
    if (!MapManager::GetInstance()->CheckMapCollision(cocos2d::Point(this->GetPosition().x, this->GetPosition().y - this->GetContentSize().height / 2), GetContentSize()))
    {
        g_pPlayerAction->g_eStatus = PlayerStatus::FALLING;
        this->g_pChampion->GravityEffect(GameEnvironment::GetInstance()->GetGravityAcceleration(), dt);
    }
    else g_pPlayerAction->g_eStatus = PlayerStatus::IDLE;
}
void Player::VoidDetect()
{
    if (MapManager::GetInstance()->IsReachTheVoid(GetPosition(), GetContentSize()))
    {
        this->g_pChampion->VoidDetect();
        this->SetPosition(cocos2d::Point(m_LastSafePosition.x, this->GetContentSize().height));
    }
}
void Player::PlayerForcing(float dt)
{
    if (g_pPlayerAction->g_bIsForce && !g_pPlayerStatics->g_bIsReverse) g_pPlayerStatics->g_fForce+=0.25;
    if (g_pPlayerStatics->g_fForce > g_pChampion->GetChampionStatics()->g_fMaxForce) g_pPlayerStatics->g_bIsReverse = true;
    if (g_pPlayerStatics->g_bIsReverse && g_pPlayerAction->g_bIsForce) g_pPlayerStatics->g_fForce-=0.25;
    if (g_pPlayerAction->g_bIsForce && g_pPlayerStatics->g_fForce <= 0) this->EndTurn();
}
void Player::CastingSkill(float dt)
{
    if (g_mChampionSkillList[g_nRunningSkillIndex]->IsFinish())
    {
        g_pPlayerAction->g_bIsShooting = false;
        this->EndTurn();
    }
}
void Player::PhysicContact_ToPlayer()
{
    if (!this->g_pChampion->GetChampionStatics()->g_bIsIgnoreCollision)
    {
        this->SetPositionToLastSafe();
    }
}
void Player::Cleaner()
{
    //this->g_pChampion->Cleaner();

    CC_SAFE_DELETE(g_pPlayerStatics);
    CC_SAFE_DELETE(g_pPlayerAction);
    //g_pChampion->release();
    //CC_SAFE_DELETE(g_pChampion);

    for (auto& x : g_mChampionSkillList)
        CC_SAFE_DELETE(x.second);
}