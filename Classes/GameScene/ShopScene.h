#ifndef __SHOP_SCENE_H__
#define __SHOP_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Item/Item.h"
#include "Item/Weapon/Weapon.h"
#include "Champion/Champion.h"
#include "User/User.h"
#include "Extention/Node_StringNTag.h"
#include "MainMenuScene.h"

class Shop : public cocos2d::Layer
{
public:
    static cocos2d::MenuItemImage *sg_pUserInformation, *sg_pUserMoney;
    static cocos2d::MenuItemImage*sg_pAccept;
    static cocos2d::Sprite *sg_pBackGround_Type;
    static cocos2d::Point sg_Space;

    static cocos2d::Sprite* sg_pIconList;
private:
	class ShopType_Display : public cocos2d::Node
	{
	public:
        virtual void Init();
        virtual void RunChild(cocos2d::Node* pNode);
        virtual void StopChild(cocos2d::Node* pNode);

	public:
		int g_nCurrentIndex, g_nMaxPage;

	protected:
        virtual void Previous(cocos2d::Ref* pSender);
        virtual void Next(cocos2d::Ref* pSender);

    protected:
		ShopType_Display()
		{
			g_nCurrentIndex = 0;
		}

    protected:
		bool p_bIsRunning = false;
		cocos2d::Menu* m_pMenu;
	};

    class Display_ItemList : public ShopType_Display
    {
    public:
        inline static Display_ItemList* GetInstance()
        {
            return sp_pInstance = (sp_pInstance != nullptr) ? sp_pInstance : new Display_ItemList();
        }
    private:
        static Display_ItemList* sp_pInstance;
        std::map<int, Item*> p_vItemsList;

    private:
        Display_ItemList() : ShopType_Display()
        {
            g_nMaxPage = p_vItemsList.size() / 3;

            if (p_vItemsList.size() % 3 > 0) g_nMaxPage += 1;
        }
    };

    class Display_ChampionList : public ShopType_Display
    {
    public:
        inline static Display_ChampionList* GetInstance()
        {
            return sp_pInstance = (sp_pInstance != nullptr) ? sp_pInstance : new Display_ChampionList();
        }
        inline std::map<int, Champion*> GetChampionList()
        {
            return p_vChampionList;
        }
        void DisplayChampion(Node* pNode);
        

    private:
        std::map<int, Champion*> p_vChampionList;

        Display_ChampionList() : ShopType_Display()
        {
            g_nMaxPage = p_vChampionList.size() / 3;

            if (p_vChampionList.size() % 3 > 0)
            {
                g_nMaxPage += 1;
            }
        }
        static Display_ChampionList* sp_pInstance;
    private:
        void ShowChampionInfor(Ref* pSender);
    };

public:
    static cocos2d::Scene* createScene();
    static void Init(cocos2d::Menu* m);

public:
    virtual void onEnter();
    virtual bool init();
    
    CREATE_FUNC(Shop);
private:
    void BackToMainMenuScene(Ref* pSender);
    void DisplayWeaponList(Ref* pSender);
    void DisplayItemList(Ref* pSender);
    void DisplayChampionList(Ref* pSender);

private:
    User* p_pUser;
    std::map<int, Weapon*> p_vWeaponsList;
};

#endif // __SHOP_SCENE_H__

