#pragma once

#ifndef __BATTLE_SCENE_H__
#define __BATTLE_SCENE_H__

#include "cocos2d.h"
#include "Factory/PlayerFactory.h"
#include "Map/Map.h"
#include "GameFight/BattleElement.h"
#include "ui/CocosGUI.h"
#include "Audio/SoundManager.h"

enum class BattleTeam
{
    TEAM_A = -1, 
    TEAM_B = 1
};

struct PlayerInBattle
{
public:
    PlayerInBattle(BattleTeam eTeam, Player* pPlayer)
    {
        g_eTeam = eTeam;
        g_pPlayer = pPlayer;
    }
public:
    BattleTeam g_eTeam;
    Player *g_pPlayer;
    bool g_bIsWin;
public:
    inline void SetWin(bool isWin) { this->g_bIsWin = isWin; }
public:
    static PlayerInBattle Create(BattleTeam eTeam, Player* pPlayer)
    {
        PlayerInBattle p = PlayerInBattle(eTeam, pPlayer);
        return p;
    }
public:
    struct SortPlayerInBattle
    {
        inline bool operator() (const PlayerInBattle lhs, const PlayerInBattle rhs)
        {
            return lhs.g_pPlayer->g_pChampion->GetStatics()->g_fSPD > rhs.g_pPlayer->g_pChampion->GetStatics()->g_fSPD;
        }
    };
};

class BattleScene : public cocos2d::Layer
{
public:
    //All static function
    //{
    static cocos2d::Scene* createScene();
    //}
public:
    //All Init function
    //{
    virtual bool init(); 
    virtual void onEnter(); 
    virtual void onExit();
    CREATE_FUNC(BattleScene); 
    //}
public:
    //All Clicker function
    //{
    void GoToPauseScene(Ref* pSender); 
    void GoToGameOverScene(Ref* pSender); 
    //}
public:
    //All Update function
    //{
    void update(float dt); 
    void playerIsTurnUpdate(float dt);
    void playerAliveUpdate(float dt);
    void cilentPlayerUpdate(float dt);
    void endGame(float dt);
    //}
public:
    //All Keyevent function
    //{
    void ClickButton(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    void EndClick(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    //}
public:
    //All physic contact function
    //{
    bool onContactBegin(cocos2d::PhysicsContact& contact);
    //}
public:
    //All physic world function
    void setPhysicsWorld(cocos2d::PhysicsWorld* pWorld);
public:
    //All function
    //{
    void DisplayPlayerStatic();
    void CalculateNewTurn();
    void CalculateNewTurn(int nIndex);
    void CalculateEndGame();
    void EndGame();
    void AutoSetTeamWinner(BattleTeam eTeam, bool isWin);

    void ClientEndGame();
    void ClientFloatingBoard(bool isWin);
    //void SetPlayerPosition(cocos2d::Point pos);
    //}
private:
    cocos2d::PhysicsWorld* p_pWorld;
    //std::vector<Player*> p_vPlayers;
    std::vector<PlayerInBattle> p_vPlayersInBattle;
    cocos2d::EventListenerPhysicsContact* p_pContactListener;
    int p_nPlayerTurnIndex = 0;
    cocos2d::Label *labelButton;
    Player* p_pClientPlayer;
    int p_nPlayerNum, p_nPlayersPerTeam;
    bool p_bIsEndGame;
    BattleTeam p_eWinner;
};

#endif // __BATTLE_SCENE_H__
