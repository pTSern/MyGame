#pragma once
#include <string>
enum class ItemTiers
{
	COMMON = 0,
	UNCOMMON = 1,
	RARE = 2,
	EPIC = 3,
	LEGENDARY = 4,
	MYTHICAL = 5,
	UNIQUE = 6
};

enum class ItemStackType
{
	ONE = 0,
	X64 = 1,
	X128 = 2
};


struct ItemStatics
{
public:
	ItemStatics(int ID = 0, std::string name = "", std::string description = "", ItemTiers itemTier = ItemTiers::COMMON, ItemStackType itemStackType = ItemStackType::ONE)
	{
		g_nID = ID;
		g_sName = name;
		g_sDescription = description;
		g_itemTier = itemTier;
		g_stackItemType = itemStackType;
	};
	int g_nID;
	std::string g_sName;
	std::string g_sDescription;
	ItemTiers g_itemTier;
	ItemStackType g_stackItemType;
};