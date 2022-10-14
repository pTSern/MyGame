#include "Login.h"

USING_NS_CC;

Scene* LoginScene::createScene()
{
    auto scene = Scene::create();

    auto layer = LoginScene::create();
    scene->addChild(layer);

    return scene;
}

bool LoginScene::init()
{
    if (!Layer::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto background = Sprite::create("ui/background.png");
    background->setPosition(Point(visibleSize / 2));
    this->addChild(background, -2);

    auto login_bg = Sprite::create("ui/lgbg.png");
    login_bg->setPosition(Point(visibleSize / 2));
    this->addChild(login_bg, -1);

    p_pLogin = ui::Button::create("ui/login_button.png");
    p_pLogin->setTitleText("Log In");
    p_pLogin->addClickEventListener(CC_CALLBACK_1(LoginScene::CheckLogin, this));
    p_pLogin->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2 + p_pLogin->getContentSize().height / 2));
    p_LoginPos = p_pLogin->getPosition();
    this->addChild(p_pLogin, 1);

    p_pPassword = ui::EditBox::create(cocos2d::Size(254, 32), "ui/login_normal.png", "ui/login_pressed.png");
    p_pPassword->setPosition(Point(visibleSize.width / 2, p_pLogin->getPosition().y + p_pLogin->getContentSize().height + p_pPassword->getContentSize().height / 2));
    p_pPassword->setFontName("fonts/facebook.ttf");
    p_pPassword->setPlaceholderFontName("fonts/facebook.ttf");
    p_pPassword->setPlaceHolder(" Password ");
    p_pPassword->setPlaceholderFontSize(12);
    p_pPassword->setMaxLength(32);
    p_pPassword->setFontColor(Color3B::BLACK);
    p_pPassword->setPlaceholderFontColor(Color3B::BLACK);
    p_pPassword->setInputFlag(ui::EditBox::InputFlag::PASSWORD);
    p_pPassword->setReturnType(ui::EditBox::KeyboardReturnType::DONE);
    this->addChild(p_pPassword, 1);

    p_pUserName = ui::EditBox::create(cocos2d::Size(254, 32), "ui/login_normal.png", "ui/login_pressed.png");
    p_pUserName->setFontName("fonts/facebook.ttf");
    p_pUserName->setPlaceholderFontName("fonts/facebook.ttf");
    p_pUserName->setPlaceHolder(" Username or Email address ");
    p_pUserName->setPlaceholderFontSize(12);
    p_pUserName->setPosition(Point(visibleSize.width / 2, p_pPassword->getPosition().y + p_pPassword->getContentSize().height + p_pUserName->getContentSize().height / 2));
    p_pUserName->setMaxLength(32);
    p_pUserName->setFontColor(Color3B::BLACK);
    p_pUserName->setPlaceholderFontColor(Color3B::BLACK);
    p_pUserName->setReturnType(ui::EditBox::KeyboardReturnType::DONE);
    this->addChild(p_pUserName, 1);

    p_pNotification = Label::createWithTTF("", "fonts/facebook.ttf", 14);
    p_pNotification->setTextColor(Color4B::RED);
    this->addChild(p_pNotification, 1);

    LogManager::GetInstance()->Log("LOGIN SCENE: init login scene successfully");

    return true;
}

void LoginScene::GoToMainMenu(Ref * pSender)
{
    auto scene = MainMenu::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(1.0, scene));

    LogManager::GetInstance()->Log("LOGIN SCENE: Go to main menu scene successfully");
}

void LoginScene::CheckLogin(Ref* pSender)
{
    std::string sUserName = p_pUserName->getText();
    std::string sPassword = p_pPassword->getText();
    //log((sUserName + " - " + sPassword).c_str());
    if (UserDataManager::GetInstance()->CheckLogin(sUserName, sPassword))
    {
        User::GetInstance()->SupperInit(sUserName, sPassword);
        //User::GetInstance()->UpdatePass("b");
        this->GoToMainMenu(pSender);
        LogManager::GetInstance()->Log("LOGIN SCENE: Login successfully");
    }
    else LoginFail(pSender);

}

void LoginScene::LoginFail(Ref* pSender)
{
    p_pNotification->setPosition(p_LoginPos);
    p_pLogin->setPosition(Point(p_LoginPos.x, p_LoginPos.y - p_pLogin->getContentSize().height));

    p_pNotification->setString("Invalid username or password");
}