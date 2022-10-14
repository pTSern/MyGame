#pragma once
#include "Item/Item.h"
#include <map>
struct ItemInInventory
{
public:
	Item* g_pItem;
	int g_nAmount;
	int g_nIndex;
};

class Inventory
{
public:
	Inventory() {}
	std::map<int, ItemInInventory*> g_mInven;
	
};

