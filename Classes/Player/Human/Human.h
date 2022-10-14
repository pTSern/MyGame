#pragma once
#include "Factory/PlayerFactory.h"
class Human : public Player
{
public:
	Human();
	virtual void ClickEvent(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	virtual void EndClickEvent(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	virtual void Cleaner();
	virtual void PlayerIsTurnUpdate(float dt);
};