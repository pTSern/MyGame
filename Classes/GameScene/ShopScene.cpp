#include "ShopScene.h"

USING_NS_CC;

Shop::Display_ChampionList* Shop::Display_ChampionList::sp_pInstance = nullptr;
Shop::Display_ItemList* Shop::Display_ItemList::sp_pInstance = nullptr;

cocos2d::MenuItemImage* Shop::sg_pUserInformation = nullptr;
cocos2d::MenuItemImage* Shop::sg_pUserMoney = nullptr;
cocos2d::Sprite* Shop::sg_pBackGround_Type = nullptr;
cocos2d::MenuItemImage* Shop::sg_pAccept = nullptr;

cocos2d::Point Shop::sg_Space(26,26);
cocos2d::Sprite* Shop::sg_pIconList = nullptr;

// SHOP TYPE DISPLAY
void Shop::ShopType_Display::Init()
{
    auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();

    auto sg_Space = cocos2d::Point(26, 26);

    auto pPage = cocos2d::Sprite::create("ui/pageview.png");
    pPage->setPosition(cocos2d::Point(Shop::sg_pIconList->getPosition().x, Shop::sg_pIconList->getContentSize().height + Shop::sg_Space.y + pPage->getContentSize().height / 2));
    this->addChild(pPage);

    auto pNext = cocos2d::MenuItemImage::create("button/arrow_normal.png", "button/arrow_clicked.png", CC_CALLBACK_1(ShopType_Display::Next, this));
    pNext->setPosition(cocos2d::Point(visibleSize.width - sg_Space.x - pNext->getContentSize().width / 2, 92 + sg_Space.y + pNext->getContentSize().height / 2));

    auto pPrevious = cocos2d::MenuItemImage::create("button/arrow_normal.png", "button/arrow_clicked.png", CC_CALLBACK_1(ShopType_Display::Previous, this));
    pPrevious->setPosition(cocos2d::Point(visibleSize.width - sg_Space.x - pNext->getContentSize().width - sg_Space.x - pPrevious->getContentSize().width / 2, 92 + sg_Space.y + pPrevious->getContentSize().height / 2));

    this->m_pMenu = cocos2d::Menu::create(pNext, pPrevious, NULL);
    m_pMenu->setPosition(cocos2d::Point::ZERO);
    m_pMenu->setLocalZOrder(Node_StringNTag::UIOrderNum());

    this->addChild(m_pMenu);
}

void Shop::ShopType_Display::RunChild(cocos2d::Node* pNode)
{
    if (!p_bIsRunning) pNode->addChild(this);

    p_bIsRunning = true;
}
void Shop::ShopType_Display::StopChild(cocos2d::Node* pNode)
{
    if (p_bIsRunning) pNode->removeChild(this);
    p_bIsRunning = false;
}

void Shop::ShopType_Display::Previous(cocos2d::Ref* pSender)
{
    if (g_nCurrentIndex > 0) g_nCurrentIndex--;
}
void Shop::ShopType_Display::Next(cocos2d::Ref* pSender)
{
    if (g_nCurrentIndex < g_nMaxPage) g_nCurrentIndex++;
}

// DISPLAY CHAMPION
void Shop::Display_ChampionList::DisplayChampion(Node* pNode)
{
    if (p_vChampionList.size() > 0)
    {
        //cocos2d::MenuItemImage* This_pC = cocos2d::MenuItemImage::create(p_vChampionList[g_nCurrentIndex]->GetChampionStatics()->g_sFileName_Selected, p_vChampionList[g_nCurrentIndex]->GetChampionStatics()->g_sFileName_Normal, CC_CALLBACK_1(Shop::Display_ChampionList::ShowChampionInfor, this));

        cocos2d::MenuItemImage* Next_pC = cocos2d::MenuItemImage::create("NULL/null.png", "NULL/null.png");
        cocos2d::MenuItemImage* Prev_pC = cocos2d::MenuItemImage::create("NULL/null.png", "NULL/null.png");

        if (g_nCurrentIndex > 0)
        {
            //Next_pC = cocos2d::MenuItemImage::create(p_vChampionList[g_nCurrentIndex + 1]->GetChampionStatics()->g_sFileName_Selected, p_vChampionList[g_nCurrentIndex + 1]->GetChampionStatics()->g_sFileName_Normal);
        }
        if (g_nCurrentIndex < g_nMaxPage)
        {
           // Prev_pC = cocos2d::MenuItemImage::create(p_vChampionList[g_nCurrentIndex - 1]->GetChampionStatics()->g_sFileName_Selected, p_vChampionList[g_nCurrentIndex - 1]->GetChampionStatics()->g_sFileName_Normal);
        }

        cocos2d::Menu* pDisplayMenu = cocos2d::Menu::create(Next_pC, Prev_pC, NULL);
        pNode->addChild(pDisplayMenu, 2);
    }

}

void Shop::Display_ChampionList::ShowChampionInfor(Ref* pSender)
{

}

// DISPLAY ITEM


// SHOP
void Shop::Init(cocos2d::Menu* m)
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    //Shop::sg_pIconList = m;
    //p_pIconList->setPosition(Point::ZERO);

    sg_pUserInformation = cocos2d::MenuItemImage::create("ui/user.png", "ui/user.png");
    sg_pUserInformation->setPosition(sg_pUserInformation->getContentSize().width/2, visibleSize.height - sg_pUserInformation->getContentSize().height / 2);

    sg_pUserMoney = cocos2d::MenuItemImage::create("ui/money.png", "ui/money.png");
    sg_pUserMoney->setPosition(sg_pUserMoney->getContentSize().width / 2, visibleSize.height - sg_pUserInformation->getContentSize().height - sg_Space.y - sg_pUserMoney->getContentSize().height / 2);

    sg_pAccept = cocos2d::MenuItemImage::create("ui/yes.png", "ui/yes.png");
    sg_pAccept->setPosition(sg_pAccept->getContentSize() / 2);

    sg_pIconList = Sprite::create("ui/iconbar.png");
    sg_pIconList->setPosition(Point(visibleSize.width - sg_pIconList->getContentSize().width / 2, 0));
}

void Shop::onEnter()
{
    Layer::onEnter();

    auto vSz = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto menu = cocos2d::Menu::create(sg_pUserInformation, sg_pUserMoney, sg_pAccept, NULL);
    menu->setPosition(Point::ZERO);

    this->addChild(menu);
    this->addChild(sg_pIconList);

    sg_pBackGround_Type = cocos2d::Sprite::create("ui/shoptype.png");
    sg_pBackGround_Type->setPosition(Point(vSz.width - sg_pBackGround_Type->getContentSize().width / 2, vSz.height - sg_pBackGround_Type->getContentSize().height / 2));
    this->addChild(sg_pBackGround_Type, 0);

    auto championType = ui::Button::create("button/button_220_normal.png", "button/button_220_clicked.png");
    championType->setTitleText("CHAMPION");
    championType->setTitleColor(Color3B::GREEN);
    championType->addClickEventListener(CC_CALLBACK_1(Shop::DisplayChampionList, this));
    championType->setPosition(Point(sg_pBackGround_Type->getPosition().x - championType->getContentSize().width, sg_pBackGround_Type->getPosition().y));
    this->addChild(championType, 1);

    auto itemType = ui::Button::create("button/button_220_normal.png", "button/button_220_clicked.png");
    itemType->setTitleText("ITEM");
    itemType->setTitleColor(Color3B::GREEN);
    itemType->addClickEventListener(CC_CALLBACK_1(Shop::DisplayItemList, this));
    itemType->setPosition(Point(sg_pBackGround_Type->getPosition().x , sg_pBackGround_Type->getPosition().y));
    this->addChild(itemType, 1);

    //auto championType = ui::Button::create("button/button_220_normal.png", "button/button_220_clicked.png");
    //championType->setTitleText("CHAMPION");
    //championType->setTitleColor(Color3B::GREEN);

    Display_ChampionList::GetInstance()->Init();
    Display_ItemList::GetInstance()->Init();

    Display_ChampionList::GetInstance()->RunChild(this);
}

Scene* Shop::createScene()
{
    auto scene = Scene::create();

    auto layer = Shop::create();
    scene->addChild(layer);
    return scene;
}
bool Shop::init()
{
    if (!Layer::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto pauseItem = MenuItemImage::create("ui/close_normal.png", "ui/close_clicked.png", CC_CALLBACK_1(Shop::BackToMainMenuScene, this));
    pauseItem->setPosition(Point(visibleSize.width - pauseItem->getContentSize().width + (pauseItem->getContentSize().width / 4) + origin.x,
        visibleSize.height - pauseItem->getContentSize().height + (pauseItem->getContentSize().width / 4) + origin.y));

    auto menu = Menu::create(pauseItem, NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu, 3);

    return true;
}

void Shop::DisplayChampionList(Ref* pSender)
{
    Display_ChampionList::GetInstance()->RunChild(this);

    Display_ItemList::GetInstance()->StopChild(this);
}

void Shop::DisplayItemList(Ref* pSender)
{
    Display_ItemList::GetInstance()->RunChild(this);

    Display_ChampionList::GetInstance()->StopChild(this);
}

void Shop::BackToMainMenuScene(Ref* pSender)
{
    auto scene = MainMenu::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(1.0, scene));
}

