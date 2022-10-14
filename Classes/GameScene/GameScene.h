#pragma once
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

#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "Champion/Champion.h"
#include "Physic/BulletPhysic_Default.h"
#include "Extention/Statics_Attributes.h"

struct CharacterSprite
{
public:
    CharacterSprite(cocos2d::Sprite* _sprite, float _time = 0, float _next_X = 0, float _next_Y = 0) 
    {
        time = _time;
        sprite = _sprite;
        next_Y = _next_Y;
        next_X = _next_X;
    };
    float time;
    cocos2d::Sprite* sprite;
    float next_X, next_Y;
};

struct asx
{
public:
    asx(cocos2d::Scene* scene, cocos2d::Sprite* xSprite)
    {
        g_scene = scene;
        g_xSprite = xSprite;
        g_xSprite->setPosition(cocos2d::Point(1024 / 2, 768 / 2));
        g_scene->addChild(g_xSprite, 1);
    }
    cocos2d::Scene* g_scene;
    cocos2d::Sprite* g_xSprite;

    void addnew()
    {
        g_scene->addChild(g_xSprite, 1);
    }
};

class GameScreen : public cocos2d::Layer
{
public:
    std::vector<CharacterSprite> chicken;
    std::vector<float> chickenTime;

    cocos2d::Sprite* backgroundSprite[2];
    cocos2d::Sprite* playerSprite;
    cocos2d::Sprite* xforce, * xmem_force;
    cocos2d::Sprite* xgui, * xb, * xag;
    BulletPhysic_Default* g_pBPD = new BulletPhysic_Default();
    //float m_fStartPoint_X, m_fStartPoint_Y;

public:

    static cocos2d::Scene* gamescene;
    static cocos2d::Scene* createScene();

    static void lmeo(cocos2d::Scene* x);
    static void bruh();

    virtual bool init(); //

    CREATE_FUNC(GameScreen); //

    void GoToPauseScene(Ref* pSender); //
    void GoToGameOverScene(Ref* pSender); //
    
    void update(float dt); //

    void SpawnChicken(float dt);

    bool SecondInit();

    void ClickButton(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    void EndClick(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    void createbullet(float dt);
    void shoot(float dt);
    void cal(float dt);
    void checkBuller(float dt);

    void setPhysicsWorld(cocos2d::PhysicsWorld* world)
    {
        mWorld = world;
        mWorld->setGravity(cocos2d::Vect(0, 0));
        //mWorld->setGravity(cocos2d::Vect(0,-m_Mass*m_Gravity));
    }
    bool onContactBegin(cocos2d::PhysicsContact& contact);
    void Gacha(Ref* pSender);
    void NewWind(Ref* pSender);
private:
    cocos2d::PhysicsWorld* mWorld;
    int playerSpeed = 0;
    int speedForce = 3;
    float cforrce, force = 0;
    bool isForce = false;
    bool isReverse = false;
    bool isAngle = false;
    bool isRA = false;

    float m_Mass = 1.0f, m_Gravity = 9.8f;

    float time = 0;
    int angle = 0;
    int c,xc = 0;
    float rotate = 0;
    float m_Friction = 0;
    float ag;
    bool doJob = false;
    DIR dir;
    int maxforce = 150;
    float next_X = 0, next_Y = 0;
    float start_Point = 0;
    int min_ag = 0, max_ag = 90;

    bool isRight = false, isLeft = false;

    int bn = 5, st = 0;

    cocos2d::Label* labelButton, *xPos, *wind;
};

#endif // __GAME_SCENE_H__
