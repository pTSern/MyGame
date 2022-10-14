#pragma once
#include "Extention/ItemManager.h"
#include "GameObject/GameObject.h"
#include "GameObject/Properties.h"
#include "Factory/GameObjectFactory.h"
#include "Extention/ShopManager.h"

const int AMOUNT_ONE = 1;
const int AMOUNT_X64 = 64;
const int AMOUNT_X128 = 128;

class Item : public GameObject
{
public:
	Item(const XProperties* pProperties);
	virtual void Update(float dt);
	virtual void Cleaner();

	inline void SetItemStatics(ItemStatics* pItemStatics) { this->m_pItemStatics = pItemStatics; }
	inline void SetItemEconomy(ShopEconomy* pItemEco) { this->m_pItemEconomy = pItemEco; }

public:
	ItemStatics* m_pItemStatics;
	ShopEconomy* m_pItemEconomy;
};

