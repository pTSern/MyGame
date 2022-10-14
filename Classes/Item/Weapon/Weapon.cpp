#include "Weapon.h"

static Register<Weapon> s_register("WEAPON");

Weapon::Weapon(const XProperties* pProperties) : Item(pProperties)
{

}

void Weapon::ConvertFromIten(Item* i)
{
	
	this->m_pItemStatics = i->m_pItemStatics;
}
void Weapon::Update(float dt)
{
	Item::Update(dt);
}
void Weapon::Cleaner()
{
	CC_SAFE_DELETE(g_pAttributes);
	CC_SAFE_DELETE(g_pStatics);
	Item::Cleaner();
}