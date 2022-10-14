#pragma once
#include "User/User.h"
#include "cocos2d.h"
#include "Extention/Statics_Attributes.h"
#include "Extention/InGameUI.h"
#include "GameFight/GameEnvironment.h"
#include "DataManager/UserData_Manager.h"
#include "Extention/PlayerManager.h"
#include "Map/Map.h"
#include "Factory/ChampionSkillFacatory.h"

class Player
{
public:
	Player();
public:
	PlayerStatics* g_pPlayerStatics;
	PlayerAction* g_pPlayerAction;
	Champion* g_pChampion;
	Statics m_pChampionStatics_InGame;
	
	InGameUI* g_pInGameUI;
	PlayerClientUI* g_pClientUI;

	std::map<SkillIndex, ChampionSkill*> g_mChampionSkillList;
	SkillIndex g_nRunningSkillIndex;

	cocos2d::EventListenerKeyboard* GetKeyboardListener();
	//std::function<void(float dt)> g_fnSelector;
public:
	struct SortManager
	{
		inline bool operator() (const Player* lhs, const Player* rhs)
		{
			return lhs->g_pChampion->GetStatics()->g_fSPD > rhs->g_pChampion->GetStatics()->g_fSPD;
		}
	};
public:
	void Cleaner();

	//Update player 
	void PlayerUpdate(float dt);
	
	void PlayerAliveUpdate(float dt);
	void PlayerUIUpdate();
	void PlayerDeadUpdate(float dt);

	void PlayerMove(float dt);
	void UpdateAngle(float dt);
	void PlayerForcing(float dt);
	bool LifeCheck(float dt);

	virtual void ClickEvent(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) = 0;
	virtual void EndClickEvent(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) = 0;
	virtual void PlayerIsTurnUpdate(float dt);

	void StartTurn();
	void EndTurn();

	void SetPosition(cocos2d::Point pos);
	void GravityEffect(float dt);
	void VoidDetect();

	void CastingSkill(float dt);
	void DoPassTurn();
	void PhysicContact_ToPlayer();
	void log()
	{
		cocos2d::log( ("POS: " + std::to_string(GetPosition().x) + std::to_string(GetPosition().y)).c_str());
	}

	bool IsValidTurn();
public:
	cocos2d::Point GetPosition();
	void SetPositionToLastSafe();
	cocos2d::Size GetContentSize();
protected:
	static cocos2d::EventListenerKeyboard* m_pListenerKeyboard;
protected:
	cocos2d::Point m_LastSafePosition;
	int p_nDelayInput = 0;
};