#include "Item.h"

static Register<Item> s_register("ITEM");

Item::Item(const XProperties* pProperties) : GameObject(pProperties)
{

}

void Item::Update(float dt)
{
	cocos2d::log("ITEM UPDATE");
	GameObject::Update(dt);
}
void Item::Cleaner()
{
	CC_SAFE_DELETE(m_pItemStatics);
	CC_SAFE_DELETE(m_pItemEconomy);
	//GameObject::Cleaner();
}