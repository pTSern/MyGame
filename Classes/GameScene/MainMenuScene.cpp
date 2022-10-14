#include "MainMenuScene.h"
#include "GameScene.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

//Menu* MainMenu::p_pIconList = nullptr;

Scene* MainMenu::createScene()
{
    auto scene = Scene::create();

    auto layer = MainMenu::create();
    scene->setName("MAIN MENU");
    scene->addChild(layer);

    return scene;
}

bool MainMenu::init()
{
    if (!Layer::init())
    {
        return false;
    }
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto pvp = MenuItemImage::create("ui/pvp.png", "ui/pvp.png", CC_CALLBACK_1(MainMenu::GoToPvP, this));
    pvp->setPosition(Point(visibleSize.width / 2 - pvp->getContentSize().width / 2, visibleSize.height / 2 + pvp->getContentSize().height / 2));

    auto shop = MenuItemImage::create("ui/shop.png", "ui/shop.png", CC_CALLBACK_1(MainMenu::GoToShop, this));
    shop->setPosition(Point(visibleSize.width / 2 + shop->getContentSize().width, visibleSize.height / 2 - shop->getContentSize().height / 3));

    auto menu = Menu::create(pvp, shop, NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu);

    auto backgroundSprite = Sprite::create("bg.png");
    backgroundSprite->setPosition(Point((visibleSize.width / 2) + origin.x, (visibleSize.height / 2) + origin.y));
    this->addChild(backgroundSprite, -1);

    auto frame = cocos2d::Sprite::create(User::GetInstance()->GetUserUITexture()->g_sFrame);
    frame->setPosition(Point(0 + frame->getContentSize().width / 2, visibleSize.height - frame->getContentSize().height / 2));
    this->addChild(frame, 1);

    auto avatar = cocos2d::Sprite::create(User::GetInstance()->GetUserUITexture()->g_sAvatar);
    avatar->setPosition(frame->getPosition());
    this->addChild(avatar, 0);
    
    auto p_pUserName = cocos2d::Label::createWithTTF(User::GetInstance()->GetUserInformation()->g_sNickname, "fonts/arial.ttf", 20);
    p_pUserName->setPosition(Point(frame->getPosition().x + frame->getContentSize().width / 1.8, visibleSize.height - 10));
    this->addChild(p_pUserName, 1);


	 auto pCoin = cocos2d::Sprite::create("ui/coin.png");
    pCoin->setPosition(Point(p_pUserName->getPosition().x*2, p_pUserName->getPosition().y));
    this->addChild(pCoin, 1);

	 auto pSp = cocos2d::Sprite::create("ui/sp.png");
	 pSp->setPosition(Point(pCoin->getPosition().x * 2, p_pUserName->getPosition().y));
    this->addChild(pSp, 1);

    
    auto p_pXu = cocos2d::Label::createWithTTF(std::to_string(User::GetInstance()->GetUserEconomy()->g_fXu), "fonts/arial.ttf", 20);
    p_pXu->setTextColor(cocos2d::Color4B::YELLOW);
    p_pXu->setPosition(Point(pCoin->getPosition().x + pCoin->getContentSize().width*3, pCoin->getPosition().y));
    this->addChild(p_pXu, 1);

    auto p_pSp = cocos2d::Label::createWithTTF(std::to_string(User::GetInstance()->GetUserEconomy()->g_fSp), "fonts/arial.ttf", 20);
    p_pSp->setTextColor(cocos2d::Color4B::BLUE);
    p_pSp->setPosition(Point(pSp->getPosition().x + pSp->getContentSize().width*3, p_pUserName->getPosition().y));
    this->addChild(p_pSp, 1);
    //User::GetInstance()->log();
    LogManager::GetInstance()->Log("MAIN MENU SCENE: init main menu scene successfully");
    return true;
}

void MainMenu::onEnter()
{
    Layer::onEnter();

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto icon = MenuItemImage::create("ui/iconbar.png", "ui/iconbar.png");
    icon->setPosition(Point(visibleSize.width - icon->getContentSize().width / 2, 0));
    p_pIconList = Menu::create(icon, NULL);
    p_pIconList->setPosition(Point::ZERO);

    SoundManager::GetInstance()->PlayMainMenuSound();

    LogManager::GetInstance()->Log("MAIN MENU SCENE: enter main menu scene successfully");
    this->addChild(p_pIconList);
}

void MainMenu::GoToGameScene(Ref * pSender)
{
    auto scene = GameScreen::createScene();
    
    Director::getInstance()->replaceScene(TransitionFade::create(1.0, scene));
}
void MainMenu::GoToPvP(Ref* pSender)
{
    auto scene = BattleScene::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(0.0, scene));

    LogManager::GetInstance()->Log("MAIN MENU SCENE: Go to battle scene successfully");
    cocos2d::log("MAIN MENU SCENE: Go to battle scene successfully");
}

void MainMenu::GoToShop(Ref* pSender)
{
    auto scene = Shop::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(1.0, scene));
    Shop::Init(p_pIconList);

    LogManager::GetInstance()->Log("MAIN MENU SCENE: Go to shop scene successfully");
}
