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

#ifndef __LOGIN_SCENE_H__
#define __LOGIN_SCENE_H__

#include "cocos2d.h"
#include "MainMenuScene.h"
#include "DataManager/UserData_Manager.h"
#include "ui/CocosGUI.h"
#include "Factory/GameObjectFactory.h"

class LoginScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

public:
    void GoToMainMenu(Ref* pSender);
    void CheckLogin(Ref* pSender);
    void LoginFail(Ref* pSender);
    CREATE_FUNC(LoginScene);
private:
    cocos2d::ui::EditBox *p_pUserName, *p_pPassword;
    cocos2d::ui::Button* p_pLogin;
    cocos2d::Label* p_pNotification;
    cocos2d::Point p_LoginPos;
    
};

#endif // __LOGIN_SCENE_H__