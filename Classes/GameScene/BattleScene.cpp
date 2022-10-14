#include "BattleScene.h"
#include "GameOverScene.h"
#include "PauseScene.h"
#include "MainMenuScene.h"

USING_NS_CC;
void BattleScene::setPhysicsWorld(cocos2d::PhysicsWorld* pWorld)
{
    p_pWorld = pWorld;
    //p_pWorld->setGravity(cocos2d::Vect(0, 0));
    p_pWorld->setGravity(cocos2d::Vect(0, 0));
}
Scene* BattleScene::createScene()
{
    auto scene = Scene::createWithPhysics();
    scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    auto layer = BattleScene::create();
    layer->setPhysicsWorld(scene->getPhysicsWorld());
    
    scene->addChild(layer);
    return scene;
}

bool BattleScene::init()
{
    if (!Layer::init())
    {
        return false;   
    }
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto pauseItem = MenuItemImage::create("pause.png","pauseClicked.png",CC_CALLBACK_1(BattleScene::GoToPauseScene, this));

    pauseItem->setPosition(Point(visibleSize.width - pauseItem->getContentSize().width + (pauseItem->getContentSize().width / 4) + origin.x, 
        visibleSize.height - pauseItem->getContentSize().height + (pauseItem->getContentSize().width / 4) + origin.y));

    auto menu = Menu::create(pauseItem, NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu);

    auto listener = EventListenerKeyboard::create();

    listener->onKeyPressed = CC_CALLBACK_2(BattleScene::ClickButton, this);
    listener->onKeyReleased = CC_CALLBACK_2(BattleScene::EndClick, this);

    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    p_pContactListener = EventListenerPhysicsContact::create();
    p_pContactListener->onContactBegin = CC_CALLBACK_1(BattleScene::onContactBegin, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(p_pContactListener, this);
    cocos2d::log("END INIT BATTLE SCENE");

    BattleElement::GetInstance()->Init(this, p_pContactListener);
    GameEnvironment::GetInstance()->Init();

    MapManager::GetInstance()->LoadTileMap("map/map_third.tmx");
    this->addChild(MapManager::GetInstance()->GetTileMap(), -3);

    labelButton = Label::createWithTTF("", "fonts/arial.ttf", 14);
    labelButton->setPosition(Point(visibleSize / 2));
    this->addChild(labelButton, 2);

    auto x = EventListenerMouse::create();

    return true;

}

void BattleScene::onEnter()
{
    Layer::onEnter();

    Player* player = PlayerFactory::GetInstance()->Create("HUMAN");
    player->SetPosition(cocos2d::Point(170, 650));
    cocos2d::log(player->g_pChampion->GetSText().c_str());
    p_pClientPlayer = player;
    this->addChild(player->g_pInGameUI);
    this->addChild(p_pClientPlayer->g_pClientUI);

    Player* bot = PlayerFactory::GetInstance()->Create("BOT");
    bot->SetPosition(cocos2d::Point(100, 550));
    bot->g_pChampion->log();
    cocos2d::log(bot->g_pChampion->GetSText().c_str());
    this->addChild(bot->g_pInGameUI);
    player->g_pPlayerAction->g_bIsTurn = true;

    //p_vPlayers.push_back(player);

    //p_vPlayers.push_back(bot);
    User::GetInstance()->OnEnterBattle();

    p_vPlayersInBattle.push_back(PlayerInBattle::Create(BattleTeam::TEAM_A, player));
    p_vPlayersInBattle.push_back(PlayerInBattle::Create(BattleTeam::TEAM_B, bot));


    this->scheduleUpdate();
    this->schedule(CC_SCHEDULE_SELECTOR(BattleScene::playerIsTurnUpdate), 0);
    this->schedule(CC_SCHEDULE_SELECTOR(BattleScene::playerAliveUpdate), 0);
    this->schedule(CC_SCHEDULE_SELECTOR(BattleScene::cilentPlayerUpdate), 0);
    this->schedule(CC_SCHEDULE_SELECTOR(BattleScene::endGame), 0);

    this->addChild(player->g_pChampion, Node_StringNTag::PlayerOrderNum(), 2);
    this->addChild(bot->g_pChampion, Node_StringNTag::PlayerOrderNum(), 2);

    p_nPlayerNum = p_vPlayersInBattle.size() + 1;
    p_nPlayersPerTeam = p_nPlayerNum / 2;
    cocos2d::log(("PLAYER PER TEAM: " +  std::to_string(p_nPlayersPerTeam)).c_str());

    BattleElement::GetInstance()->Cheat_SetPlayerClient(p_pClientPlayer);
    this->addChild(GameEnvironment::GetInstance()->GetWindTexture(), -3);

    cocos2d::log("END ON ENTER BATTLE SCENE");

    SoundManager::GetInstance()->PlayGameFightSound();
}

void BattleScene::GoToGameOverScene(Ref* pSender)
{
    auto scene = GameOver::createScene();

    Director::getInstance()->replaceScene(scene);

}

void BattleScene::GoToPauseScene(Ref* pSender)
{
    auto scene = MainMenu::createScene();

    //Director::getInstance()->pushScene(scene);
    Director::getInstance()->replaceScene(scene);
    User::GetInstance()->ReLoadSelectedChampionId();
}

void BattleScene::update(float dt)
{
    //std::sort(p_vPlayers.begin(), p_vPlayers.end(), Player::SortManager());
    std::sort(p_vPlayersInBattle.begin(), p_vPlayersInBattle.end(), PlayerInBattle::SortPlayerInBattle());
    //BattleElement::GetInstance()->Cheat_SetPlayerPos(p_pClientPlayer->GetPosition());
    //BattleElement::GetInstance()->Cheat_SetPlayerDir(p_pClientPlayer->g_pPlayerStatics->g_eDir);
    //BattleElement::GetInstance()->Cheat_SetPlayerStatus(p_pClientPlayer->g_pPlayerAction->g_eStatus);
    //Update all player in vector
    for (auto& x : p_vPlayersInBattle)
    {
        x.g_pPlayer->PlayerUpdate(dt);
        //x->log();
    }
}
void BattleScene::cilentPlayerUpdate(float dt)
{
    p_pClientPlayer->g_pClientUI->DisplayForce(p_pClientPlayer->g_pPlayerStatics->g_fForce,p_pClientPlayer->g_pChampion->GetChampionStatics()->g_fMaxForce);
    p_pClientPlayer->g_pClientUI->DisplayForceMemory(p_pClientPlayer->g_pPlayerStatics->g_fForceMemory,p_pClientPlayer->g_pChampion->GetChampionStatics()->g_fMaxForce);
    /*p_pClientPlayer->g_pInGameUI->Set_HPSTM_BarPosition(cocos2d::Point(p_pClientPlayer->GetPosition().x, p_pClientPlayer->GetPosition().y - p_pClientPlayer->GetContentSize().height / 1.5));
    p_pClientPlayer->g_pInGameUI->Display_HP_Bar(p_pClientPlayer->g_pChampion->GetStatics()->g_fHP, p_pClientPlayer->g_pChampion->GetStatics()->g_fMAX_HP);
    p_pClientPlayer->g_pInGameUI->Display_STM_Bar(p_pClientPlayer->g_pChampion->GetStatics()->g_fCurrent_STM, p_pClientPlayer->g_pChampion->GetStatics()->g_fMAX_STAMINA);*/
}
void BattleScene::playerAliveUpdate(float dt)
{
    for (auto& x : p_vPlayersInBattle)
    {
        if (x.g_pPlayer->LifeCheck(dt)) x.g_pPlayer->PlayerAliveUpdate(dt);
    }
}

void BattleScene::playerIsTurnUpdate(float dt)
{
    //labelButton->setString( std::to_string(this->p_vPlayersInBattle[p_nPlayerTurnIndex].g_pPlayer->g_pChampion->GetStatics()->g_fHP) + " - " + std::to_string(this->p_vPlayersInBattle[p_nPlayerTurnIndex].g_pPlayer->g_pPlayerStatics->g_fForce) + " POS: " + std::to_string(this->p_vPlayersInBattle[p_nPlayerTurnIndex].g_pPlayer->GetPosition().x) + " - " + std::to_string(this->p_vPlayersInBattle[p_nPlayerTurnIndex].g_pPlayer->GetPosition().y));
    //cocos2d::log(std::to_string(this->p_vPlayers[p_nPlayerTurnIndex]->g_pPlayerStatics->g_fForce).c_str());
    this->p_vPlayersInBattle[p_nPlayerTurnIndex].g_pPlayer->PlayerIsTurnUpdate(dt);

    if (p_vPlayersInBattle[p_nPlayerTurnIndex].g_pPlayer->g_pPlayerAction->g_eStatus == PlayerStatus::END_TURN)
    {
        cocos2d::log("END TURNED");
        this->CalculateNewTurn(p_nPlayerTurnIndex);
    }
}
void BattleScene::endGame(float dt)
{
    if (p_bIsEndGame)
    {
        //Stop this update loop
        this->unschedule(CC_SCHEDULE_SELECTOR(BattleScene::endGame));
        //Call end game func
        this->EndGame();
        //Break this func
        return;
    }
    
    this->CalculateEndGame();
}
void BattleScene::ClickButton(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
    this->p_vPlayersInBattle[p_nPlayerTurnIndex].g_pPlayer->ClickEvent(keyCode, event);
}

void BattleScene::EndClick(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
    this->p_vPlayersInBattle[p_nPlayerTurnIndex].g_pPlayer->EndClickEvent(keyCode, event);
}

bool BattleScene::onContactBegin(cocos2d::PhysicsContact& contact)
{
    auto pNodeA = contact.getShapeA()->getBody()->getNode();
    auto pNodeB = contact.getShapeB()->getBody()->getNode();
    
    //Bullet contact to player
    if (dynamic_cast<Bullet*>(pNodeA) && dynamic_cast<Champion*>(pNodeB) )
    {
        log("CONTACT");
        dynamic_cast<Bullet*>(pNodeA)->ContactToPlayer();
        dynamic_cast<Champion*>(pNodeB)->GetHit(dynamic_cast<Bullet*>(pNodeA)->GetSkillStatics());
        
        this->playerAliveUpdate(0);
    }
    else if (dynamic_cast<Champion*>(pNodeA) && dynamic_cast<Bullet*>(pNodeB))
    {
        dynamic_cast<Bullet*>(pNodeB)->ContactToPlayer();
        dynamic_cast<Champion*>(pNodeA)->GetHit(dynamic_cast<Bullet*>(pNodeB)->GetSkillStatics());

        this->playerAliveUpdate(0);
    }

    return true;
}
////////////////////////////////////////////////
void BattleScene::CalculateNewTurn()
{
    int nNextIndex = 0;
    //Recaculate player turn -> finding player's is turn index
    if (p_nPlayerTurnIndex + 1 <= this->p_vPlayersInBattle.size() - 1)
    {
        nNextIndex = p_nPlayerTurnIndex + 1;
    }
    if (this->p_vPlayersInBattle[nNextIndex].g_pPlayer->IsValidTurn())
    {
        this->p_vPlayersInBattle[nNextIndex].g_pPlayer->StartTurn();
        p_nPlayerTurnIndex = nNextIndex;
    }
    
}
void BattleScene::CalculateNewTurn(int nIndex)
{
    int nNextIndex = 0;
    if (nIndex + 1 <= this->p_vPlayersInBattle.size() - 1)
    {
        nNextIndex = nIndex + 1;
    }
    if (this->p_vPlayersInBattle[nNextIndex].g_pPlayer->IsValidTurn())
    {
        GameEnvironment::GetInstance()->GenerateWindForce();
        this->p_vPlayersInBattle[nNextIndex].g_pPlayer->StartTurn();
        p_nPlayerTurnIndex = nNextIndex;
        
    }
    else
    {
        this->CalculateNewTurn(nNextIndex);
    }
}

void BattleScene::onExit()
{
    cocos2d::log("ON EXIT BATTLE SCENE");
    Layer::onExit();
    
    for (auto& x : p_vPlayersInBattle)
       x.g_pPlayer->Cleaner();

    for (auto& x : p_vPlayersInBattle)
        CC_SAFE_DELETE(x.g_pPlayer);

    //labelButton->release();
    //p_pContactListener->release();
    //CC_SAFE_DELETE(p_pClientPlayer);
    
    cocos2d::log("FINISH ON EXIT BATTLE SCENCE");
}
void BattleScene::CalculateEndGame()
{
    int nDeathCount_A = 0;
    int nDeathCount_B = 0;
    //BattleTeam oposite = (BattleTeam)((-1) * (int)(this->p_vPlayersInBattle[p_nPlayerTurnIndex].g_eTeam));
    for (auto& x : p_vPlayersInBattle)
    {
        if (x.g_eTeam == BattleTeam::TEAM_A)
        {
            if (x.g_pPlayer->g_pChampion->GetChampionAction() == ChampionAction::DEATH)
            {
                nDeathCount_A++;
            }
        }

        if (x.g_eTeam == BattleTeam::TEAM_B)
        {
            if (x.g_pPlayer->g_pChampion->GetChampionAction() == ChampionAction::DEATH)
            {
                nDeathCount_B++;
            }
        }
    }
    if (nDeathCount_A == p_nPlayersPerTeam)
    {
        p_bIsEndGame = true;
        p_eWinner = BattleTeam::TEAM_B;
    }
    if (nDeathCount_B == p_nPlayersPerTeam)
    {
        p_bIsEndGame = true;
        p_eWinner = BattleTeam::TEAM_A;
    }
}
void BattleScene::EndGame()
{
    //run last update
        
    //stop update
    /*this->unscheduleUpdate();
    this->unschedule(CC_SCHEDULE_SELECTOR(BattleScene::playerIsTurnUpdate));
    this->unschedule(CC_SCHEDULE_SELECTOR(BattleScene::playerAliveUpdate));
    this->unschedule(CC_SCHEDULE_SELECTOR(BattleScene::cilentPlayerUpdate));*/

    //Remove all event listener -> player cant contact to game
    this->getEventDispatcher()->removeAllEventListeners();

    //Set attacker team is winner
    AutoSetTeamWinner(p_eWinner, true);

    //Set oposite team is loser
    AutoSetTeamWinner((BattleTeam)((-1)*(int)(p_eWinner)), false);

    //Update user game data
    this->ClientEndGame();
}

void BattleScene::AutoSetTeamWinner(BattleTeam eTeam, bool isWin)
{
    for (auto& x : p_vPlayersInBattle)
    {
        if (x.g_eTeam == eTeam)
        {
            x.SetWin(isWin);
        }
    }
}
void BattleScene::ClientEndGame()
{
    bool isWin = false;
    for (auto& x : p_vPlayersInBattle)
    {
        if (x.g_pPlayer == p_pClientPlayer)
        {
            isWin = x.g_bIsWin;
            break;
        }
    }
    this->ClientFloatingBoard(isWin);
    User::GetInstance()->OnExitBattle(isWin);
}
void BattleScene::ClientFloatingBoard(bool isWin)
{
    auto visibleSize = Director::getInstance()->getVisibleSize();

    cocos2d::Sprite* fb;
    if (isWin) fb = cocos2d::Sprite::create("ui/victory.png");
    else fb = cocos2d::Sprite::create("ui/defeated.png");
    fb->setPosition(visibleSize / 2);
    this->addChild(fb, 5);

    auto accept = ui::Button::create("button/button_220_normal.png", "button/button_220_clicked.png");
    accept->setTitleText("CONTINUTE");
    accept->setTitleColor(Color3B::WHITE);
    accept->addClickEventListener(CC_CALLBACK_1(BattleScene::GoToPauseScene, this));
    accept->setPosition(cocos2d::Point(visibleSize.width/2, visibleSize.height/4));
    this->addChild(accept, 5);
}