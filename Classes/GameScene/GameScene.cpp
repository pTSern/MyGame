/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

 http://www.cocos2d-x.org

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/
#include <algorithm>
#include "GameScene.h"
#include "GameOverScene.h"
#include "PauseScene.h"
#include <string>
#include <iostream>
#include "ui/CocosGUI.h"
#include <math.h>
#include <CCEventKeyboard.h>
#include "Map/Map.h"
#include "Extention/GameRandom.h"

USING_NS_CC;

const int BACKGROUND_NUM = 2;

Scene* GameScreen::gamescene = nullptr;

void GameScreen::lmeo(cocos2d::Scene* x) 
{
    gamescene = x;
    gamescene = Director::getInstance()->getRunningScene();
}

void GameScreen::bruh()
{
    asx* uwu = new asx(gamescene, Sprite::create("resume.png"));
}

Scene* GameScreen::createScene()
{
    auto scene = Scene::createWithPhysics();

    auto layer = GameScreen::create();
    layer->setPhysicsWorld(scene->getPhysicsWorld());

    scene->addChild(layer);
    return scene;
}

bool GameScreen::init()
{
    //////////////////////////////
    // 1. super init first
    log("1111111111111111");
    if (!Layer::init())
    {
        return false;   
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto pauseItem = MenuItemImage::create("pause.png","pauseClicked.png",CC_CALLBACK_1(GameScreen::GoToPauseScene, this));

    pauseItem->setPosition(Point(visibleSize.width - pauseItem->getContentSize().width + (pauseItem->getContentSize().width / 4) + origin.x, 
        visibleSize.height - pauseItem->getContentSize().height + (pauseItem->getContentSize().width / 4) + origin.y));

    auto menu = Menu::create(pauseItem, NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu);

    //Handle background scrolling
    for (int i = 0; i < BACKGROUND_NUM; i++)
    {
        backgroundSprite[i] = Sprite::create("bg.png");
        backgroundSprite[i]->setPosition(Point( (visibleSize.width / 2), (-1 * visibleSize.height * i) + (visibleSize.height / 2)) );

        this->addChild(backgroundSprite[i], -10);
    }
    //Handle player sprite
    playerSprite = Sprite::create("player.png");
    playerSprite->setPosition(Point(playerSprite->getContentSize().width, visibleSize.height/2 ));

    auto body = PhysicsBody::createBox(playerSprite->getContentSize());
    body->setContactTestBitmask(true);
    body->setDynamic(true);
    playerSprite->setPhysicsBody(body);

    this->addChild(playerSprite, -1, "player");

    this->scheduleUpdate();

    //this->schedule(CC_SCHEDULE_SELECTOR(GameScreen::SpawnChicken), 1.0);

    //Keyboard handle
    auto listener = EventListenerKeyboard::create();

    listener->onKeyPressed = CC_CALLBACK_2(GameScreen::ClickButton, this);
    listener->onKeyReleased = CC_CALLBACK_2(GameScreen::EndClick, this);

    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    //Handle force
    xforce = Sprite::create("force_dice.png");
    xforce->setAnchorPoint(Point(0,1));

    xmem_force = Sprite::create("force_memory.png");
    xmem_force->setAnchorPoint(Point(0, 1));

    xgui = Sprite::create("skill_layer.png");
    xgui->setPosition(Point(visibleSize.width / 2, xgui->getContentSize().height/2));

    xb = Sprite::create("bullet/z.png");
    
    xag = Sprite::create("angel.png");
    xag->setAnchorPoint(Point(0,0.5));

    this->addChild(xmem_force, -1);
    this->addChild(xgui, 1);
    this->addChild(xforce, 0);
    this->addChild(xb, 1);
    this->addChild(xag, -1);
    
    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(GameScreen::onContactBegin, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);

    labelButton = Label::createWithTTF("", "fonts/arial.ttf", 14);
    labelButton->setPosition(Point(visibleSize/2));
    this->addChild(labelButton, 2);

    wind = Label::createWithTTF("", "fonts/arial.ttf", 14);
    wind->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2 +100));
    this->addChild(wind, 2);

    xPos = Label::createWithTTF("", "fonts/arial.ttf", 14);
    xPos->setPosition(Point(visibleSize.width/2, visibleSize.height/2 - 50));
    this->addChild(xPos, 2);

    //asx* uwu = new asx(dynamic_cast<cocos2d::Scene*>(this), Sprite::create("resume.png"));

    MapManager::GetInstance()->LoadTileMap("map/map_first.tmx");
    this->addChild(MapManager::GetInstance()->GetTileMap(), -9);
    
   auto gachaButton = MenuItemImage::create("pause.png", "pauseClicked.png", CC_CALLBACK_1(GameScreen::Gacha, this));
   auto windButton = MenuItemImage::create("pause.png", "pauseClicked.png", CC_CALLBACK_1(GameScreen::NewWind, this));


   gachaButton->setPosition(Point(300,400));
   windButton->setPosition(Point(600, 400));
    auto x = Menu::create(gachaButton, windButton, NULL);
    x->setPosition(Point::ZERO);
    Node* pNode = Node::create();
    pNode->addChild(x);
    
    this->addChild(pNode);

    return true;
}

void GameScreen::Gacha(Ref* pSender)
{
    int x = random(1, 99);
    int f = random(1,99);
    float rate = x + (float)f / 100;
    log("%f", rate);
    if (GameRandom::GetInstance()->GetRandom(rate))
    {
        log("TRUEEEEEEEEEEEEEEEEEE");
    }
    else log("NOOOOOOOOOOO");
 
  
}

void GameScreen::NewWind(Ref* pSender)
{
    GameEnvironment::GetInstance()->GenerateWindForce();
}

void GameScreen::ClickButton(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    if (!doJob)
    {
        switch (keyCode)
        {
            case EventKeyboard::KeyCode::KEY_D:
                if (keyCode != EventKeyboard::KeyCode::KEY_A)
                {
                    dir = RIGHT;
                    playerSprite->setFlippedX(true);
                    playerSpeed++;
                    isRight = true;
                }
                break;
            case EventKeyboard::KeyCode::KEY_A:
                if (keyCode != EventKeyboard::KeyCode::KEY_D)
                {
                    dir = LEFT;
                    playerSprite->setFlippedX(false);
                    xag->setFlippedX(false);
                    playerSpeed--;
                    isLeft = true;
                }
                break;
            case EventKeyboard::KeyCode::KEY_W:
                isAngle = true;
                //log("%d", angle);
                break;
            case EventKeyboard::KeyCode::KEY_S:
                isRA = true;
                //log("%d", angle);
                break;
            case EventKeyboard::KeyCode::KEY_SPACE:
                isForce = true;
                break;
        };
    }
}

void GameScreen::EndClick(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    if (!doJob)
    {
        switch (keyCode)
        {
        case EventKeyboard::KeyCode::KEY_D:
            playerSpeed = 0;
            isRight = false;
            break;
        case EventKeyboard::KeyCode::KEY_A:
            playerSpeed = 0;
            isLeft = false;
            
            break;
        case EventKeyboard::KeyCode::KEY_SPACE:
            isForce = false;
            cforrce = force;
            force = 0;
            xmem_force->setPosition(Point(247 - xforce->getContentSize().width + (xforce->getContentSize().width * cforrce / maxforce), visibleSize.height - 740));
            
            this->schedule(CC_SCHEDULE_SELECTOR(GameScreen::createbullet), 0.5);
            this->schedule(CC_SCHEDULE_SELECTOR(GameScreen::shoot), 0);
            doJob = true;
            playerSpeed = 0;
            break;
        case EventKeyboard::KeyCode::KEY_W:
            isAngle = false;
            break;
        case EventKeyboard::KeyCode::KEY_S:
            isRA = false;
            break;
        };
    }
    
}

void GameScreen::GoToGameOverScene(Ref* pSender)
{
    auto scene = GameOver::createScene();

    Director::getInstance()->replaceScene(scene);

}

void GameScreen::GoToPauseScene(Ref* pSender)
{
    auto scene = PauseMenu::createScene();

    Director::getInstance()->pushScene(scene);

}

void GameScreen::update(float dt)
{
    cocos2d::log("UPDATEEEEEEEEEE");
    wind->setString(std::to_string(GameEnvironment::GetInstance()->GetWindForce()));

    std::string c = std::to_string(angle);
    labelButton->setString(c);

    std::string zPos = std::to_string(playerSprite->getPosition().x);
    std::string yPos = std::to_string(playerSprite->getPosition().y);
    std::string sPos = zPos + " - " + yPos;
    xPos->setString(sPos);
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleSize();
    if (isAngle && angle < max_ag) angle++; 
    if (isRA && angle > min_ag) angle--;
    playerSprite->runAction(MoveBy::create(0, Point(playerSpeed * speedForce, 0)));
    //playerSprite->setPosition(Point(playerSprite->getPosition().x + (playerSpeed * 1.0), playerSprite->getPosition().y));
    xag->setPosition(Point(playerSprite->getPosition().x, playerSprite->getPosition().y));

    if (dir == RIGHT) xag->setRotation(360 - angle);
    else xag->setRotation(180 + angle);

    if (isForce) force++;
    if (force >= maxforce) isReverse = true;
    if (isReverse && isForce) { force -= 2; if (force <= 0) { isReverse = false; isForce = false;} };

    //log("%d", force);

    xforce->setPosition(Point(247 - xforce->getContentSize().width + (xforce->getContentSize().width * force / maxforce), visibleSize.height - 740));

    if (playerSprite->getPosition().x <= 0 + playerSprite->getContentSize().width / 2) playerSprite->setPositionX(playerSprite->getContentSize().width / 2);

    if (playerSprite->getPosition().x >= visibleSize.width - playerSprite->getContentSize().width / 2) playerSprite->setPositionX(visibleSize.width - playerSprite->getContentSize().width / 2);
   
//for (int i = 0; i < BACKGROUND_NUM; i++)
//{
//    if (backgroundSprite[i]->getPosition().y >= visibleSize.height + (visibleSize.height / 2) - 1)
//    {
//        backgroundSprite[i]->setPosition(Point( visibleSize.width / 2 + origin.x, (-1 * visibleSize.height) + visibleSize.height / 2 ));
//    }
//}

//for (int i = 0; i < BACKGROUND_NUM; i++)
//{
//    backgroundSprite[i]->setPosition(Point(backgroundSprite[i]->getPosition().x, backgroundSprite[i]->getPosition().y + (0.75 * visibleSize.height * dt)));
//}

//for (int i = 0; i < chicken.size(); i++)
//{
//    chicken[i]->setPosition(Point(chicken[i]->getPosition().x, chicken[i]->getPosition().y + (0.75 * visibleSize.height * dt)));

//    if (chicken[i]->getPosition().y > visibleSize.height * 2)
//    {
//        this->removeChild(chicken[i]);
//        chicken.erase(chicken.begin() + i);
//    }
//}
}

void GameScreen::createbullet(float dt)
{
    cocos2d::log("CREATE BULLET");
    log("%f - %f", playerSprite->getContentSize().height, playerSprite->getContentSize().width);
    c++;
    Sprite* tempChicken = Sprite::create("bullet/z.png");
    CharacterSprite cs = CharacterSprite(tempChicken);

    //tempChicken->setPosition(Point(playerSprite->getPosition().x, playerSprite->getPosition().y));
    //chickenTime.push_back(0);
    chicken.push_back(cs);

    auto body = PhysicsBody::createBox(chicken[chicken.size() - 1].sprite->getContentSize());
    body->setContactTestBitmask(true);
    body->setDynamic(false);
    chicken[chicken.size() - 1].sprite->setPhysicsBody(body);

    this->addChild(chicken[chicken.size() - 1].sprite, 1, "bullet");

    g_pBPD->CalculateStartPoint(playerSprite, chicken[chicken.size() - 1].sprite, dir, angle * PI / 180);


    //xb->setRotation(rotate);
    //xb->setPosition(Point( playerSprite->getPosition().x + ( force*cos(ag)*cos(ag)*time + m_Friction*cos(ag)*time ) / m_Mass , 
    //    playerSprite->getPosition().y + ( m_Gravity*sin(ag)*time + force*sin(ag)*sin(ag)*time ) / m_Mass - 0.5*m_Gravity*time*time));

    //xb->setPosition(Point(playerSprite->getPosition().x + force*cos(ag)*time, playerSprite->getPosition().y + force*sin(ag)*time - 0.5*m_Gravity*time*time));

    //log("%f", time);
    //log("%d", force);
    //log("%f - %f", xb->getPosition().x, xb->getPosition().y);
    //log("-----------------");

    //if (xb->getPosition().x > visibleSize.width * 2 || xb->getPosition().y > visibleSize.height * 2 || xb->getPosition().x <= -visibleSize.width*2 || xb->getPosition().y <= -visibleSize.height * 2)
    //{
    //    force = 0;
    //    unschedule(CC_SCHEDULE_SELECTOR(GameScreen::shoot));
    //    this->removeChild(xb);
    //    this->addChild(xb,1);
    //}
    log("-----------------------------------------------Time: %d", c);
    if (c == bn)
    {
        c = 0;
        unschedule(CC_SCHEDULE_SELECTOR(GameScreen::createbullet));
        this->schedule(CC_SCHEDULE_SELECTOR(GameScreen::checkBuller), 0.0);
    }
}

void GameScreen::checkBuller(float dt)
{
    cocos2d::log("CHECK BULLET");
    if (st == bn) 
    { 
        cforrce = 0; 
        st = 0;
        unschedule(CC_SCHEDULE_SELECTOR(GameScreen::shoot)); 
        unschedule(CC_SCHEDULE_SELECTOR(GameScreen::checkBuller));
        doJob = false; 
        log("---------------------");
    }
}

void GameScreen::shoot(float dt)
{
    cocos2d::log("SHOOTINGGG");
    auto visibleSize = Director::getInstance()->getVisibleSize();


    ag = angle * PI / 180;
    //log("%d", chicken.size());
    if (chicken.size() > 0)
    {
        rotate += (dt*500);
        //xmem_force->setPosition(Point(247 - xforce->getContentSize().width + (xforce->getContentSize().width * force / maxforce), visibleSize.height - 740));
    }
    //log("%f", dt);
    //cforrce-=0.1;
    //log("%f", cforrce);
    for (int i = 0; i < chicken.size(); i++)
    {
        //chickenTime[i] += 0.05;
        chicken[i].time += (dt*12);

        //if (0 <= angle && angle < 45)
        //{
        //    next_X = playerSprite->getPosition().x + dir * playerSprite->getContentSize().width / 2 + 1 + dir * chicken[i].sprite->getContentSize().width / 2 + dir * ((cforrce * cos(ag) * cos(ag) * chicken[i].time + dir * m_Friction * cos(ag) * chicken[i].time) / m_Mass);
        //    next_Y = playerSprite->getPosition().y + tan(ag) * playerSprite->getContentSize().width / 2 + 1 + (m_Gravity * sin(ag) * chicken[i].time + cforrce * sin(ag) * sin(ag) * chicken[i].time) / m_Mass - 0.5 * m_Gravity * chicken[i].time * chicken[i].time;
        //}
        //else if (45 <= angle && angle <= 90)
        //{
        //    next_X = playerSprite->getPosition().x + dir * ((playerSprite->getContentSize().height/ 2) * tan(PI/2 - ag)) + 1 + dir * ((cforrce * cos(ag) * cos(ag) * chicken[i].time + dir * m_Friction * cos(ag) * chicken[i].time) / m_Mass);
        //    next_Y = playerSprite->getPosition().y + playerSprite->getContentSize().height / 2 + 1 + chicken[i].sprite->getContentSize().height / 2 + ((m_Gravity * sin(ag) * chicken[i].time + cforrce * sin(ag) * sin(ag) * chicken[i].time) / m_Mass - 0.5 * m_Gravity * chicken[i].time * chicken[i].time);
        //}

        //log("i: %d <> x: %f - y: %f", i, next_X, next_Y);
        //chicken[i].sprite->setPosition(Point(next_X, next_Y));
        chicken[i].sprite->setPosition(g_pBPD->NextXY(chicken[i].time, cforrce, dir, ag, 1));
        chicken[i].sprite->setRotation(rotate);

        //log("%f - %f", chicken[i]->getPosition().x, chicken[i]->getPosition().y);
        //if (chicken[i]->getPhysicsBody()->getCollisionBitmask() == playerSprite->getPhysicsBody()->getCollisionBitmask())
        //{
        //    //log("%d - %d", chicken[i]->getPhysicsBody()->getCollisionBitmask(), playerSprite->getPhysicsBody()->getCollisionBitmask());
        //    /*log("%f - %f", chicken[i]->getPosition().x, chicken[i]->getPosition().y);
        //    chickenTime.erase(chickenTime.begin() + i);
        //    this->removeChild(chicken[i]);
        //    chicken.erase(chicken.begin() + i);*/
        //}
        //else 
        if (chicken[i].sprite->getPosition().x > visibleSize.width * 2 || chicken[i].sprite->getPosition().y > visibleSize.height * 2 || chicken[i].sprite->getPosition().x <= -visibleSize.width * 2 || chicken[i].sprite->getPosition().y <= -visibleSize.height * 2)
        {
            CharacterSprite x = chicken[i];
            chicken.erase(chicken.begin() + i);
            this->removeChild(x.sprite);
            //this->removeChild(chicken[i].sprite);
            //chicken.erase(chicken.begin() + i);
            st++;
            log("DESSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS");
            //xc++;
        }
        
        //log("%d", chicken.size());
    }

    //log("%d", xc);
    
}

void GameScreen::cal(float dt)
{
    
}

void GameScreen::SpawnChicken(float dt)
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    int chickenIndex = cocos2d::random(0,2) + 1;

    std::string chickenString = StringUtils::format("Chicken_%d.png", chickenIndex);

    Sprite* tempChicken = Sprite::create(chickenString);

    int xRandomPos = (cocos2d::random(0, 10000) % (int)(visibleSize.width - tempChicken->getContentSize().width / 2)) + (tempChicken->getContentSize().width / 2);

    tempChicken->setPosition(Point(xRandomPos + origin.x, tempChicken->getContentSize().height + origin.y));
    CharacterSprite cs = CharacterSprite(tempChicken);


    chicken.push_back(cs);

    this->addChild(chicken[chicken.size() - 1].sprite, -1);
}

bool GameScreen::onContactBegin(PhysicsContact& contact)
{
    cocos2d::log("START CONTACT");
    auto node = contact.getShapeA()->getBody()->getNode();
    auto node2 = contact.getShapeB()->getBody()->getNode();
    //this->removeChild(node);
    //chicken.erase(std::remove_if(chicken.begin(), chicken.end(), node), chicken.end());
    for (int i = 0; i < chicken.size(); i++)
    {
        
        if (chicken[i].sprite == node)
        {
            if (node->getName() != node2->getName())
            {
                std::string ss = node->getName() + " - " + node2->getName();
                log(ss.c_str());
                log(">> %d - %d", node->getTag() != node2->getTag());
                this->removeChild(chicken[i].sprite);
                chicken.erase(chicken.begin() + i);
                st++;
                log("HITTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT");
                break;
            }
            //else if (node->getName() == node2->getName())
            //{
            //    for (int j = 0; j < chicken.size(); j++)
            //    {
            //        if (chicken[j].sprite == node2)
            //        {
            //            //log("j: %d - i: %d ", j, i);
            //            chicken[j].sprite->setTexture("bullet/x.png");
            //            this->removeChild(chicken[i].sprite);
            //            chicken.erase(chicken.begin() + i);
            //            st++;
            //            log("COMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM");
            //            break;
            //        }
            //    }
            //    break;
            //}
        }
    }

    //node->removeFromParent();


    return true;
}