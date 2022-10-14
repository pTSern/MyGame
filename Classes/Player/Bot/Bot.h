#pragma once
#include "Factory/PlayerFactory.h"
#include "Factory/Bot_Factory.h"
#include "GameFight/BattleElement.h"
enum class AI_Angle 
{
	UP,
	DOWN,
	DEFAULT
};
class Bot : public Player
{
public:
	Bot();
	virtual void ClickEvent(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	virtual void EndClickEvent(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	virtual void Cleaner();
	virtual void PlayerIsTurnUpdate(float dt);
private:
	void AutoSetDir();
	void AutoMove();
	void AutoForce();
	void AutoSkill();
	void AutoAngle(AI_Angle aia);
private:
	AI* p_pAIBrain;
};