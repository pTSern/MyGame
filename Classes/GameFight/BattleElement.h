#pragma once
#include "cocos2d.h"
#include "Extention/Statics_Attributes.h"
#include "Extention/PlayerManager.h"
#include "Player/Player.h"
class BattleElement
{
public:
	inline static BattleElement* GetInstance()
	{
		return sp_pInstance = (sp_pInstance != nullptr) ? sp_pInstance : new BattleElement();
	}
	inline int GetBattleRound()
	{
		return this->p_nGameRound;
	}
	inline void NewRound()
	{
		this->p_nGameRound++;
	}
	inline void Init(cocos2d::Node* pBattleScene, cocos2d::EventListenerPhysicsContact* pContactListener)
	{
		this->p_nGameRound = 0;
		this->p_pBattleScene = pBattleScene;
		this->p_pContactListener = pContactListener;
	}
	inline void Init(cocos2d::Node* pBattleScene, cocos2d::EventListenerPhysicsContact* pContactListener, Player* pPlayer)
	{
		this->p_nGameRound = 0;
		this->p_pBattleScene = pBattleScene;
		this->p_pContactListener = pContactListener;
		this->p_pPlayer = pPlayer;
	}
	inline cocos2d::Node* GetBattleScene()
	{
		return this->p_pBattleScene;
	}
	inline cocos2d::EventListenerPhysicsContact* GetEventListener()
	{
		return this->p_pContactListener;
	}
	inline cocos2d::Point Cheat_GetPlayerPos()
	{
		return this->p_pPlayer->GetPosition();
		//return this->p_pPlayerPos;
	}
	inline void Cheat_SetPlayerPos(cocos2d::Point pPlayerPos)
	{
		this->p_pPlayerPos = pPlayerPos;
	}
	inline DIR Cheat_GetPlayerDir()
	{
		return this->p_pPlayer->g_pPlayerStatics->g_eDir;
		//return p_pDir;;
	}
	inline void Cheat_SetPlayerDir(DIR d)
	{
		this->p_pDir = d;
	}
	inline void Cheat_SetPlayerStatus(PlayerStatus eS)
	{
		this->p_ePlayerStatus = eS;
	}
	inline PlayerStatus Cheat_GetPlayerStatus()
	{
		//return this->p_ePlayerStatus;
		return this->p_pPlayer->g_pPlayerAction->g_eStatus;
	}
	inline void Cheat_SetPlayerClient(Player *pP)
	{
		this->p_pPlayer = pP;
	}
	inline cocos2d::Size GetVisibleSize()
	{
		return cocos2d::Size(1024, 768);
	}
private:
	BattleElement();
	int p_nGameRound = 0;
	cocos2d::Node* p_pBattleScene;
	cocos2d::EventListenerPhysicsContact* p_pContactListener;
	static BattleElement* sp_pInstance;

	Player* p_pPlayer;

	cocos2d::Point p_pPlayerPos;
	DIR p_pDir;
	PlayerStatus p_ePlayerStatus;
};