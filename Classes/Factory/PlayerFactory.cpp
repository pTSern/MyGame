#include "PlayerFactory.h"
PlayerFactory* PlayerFactory::p_pInstance = nullptr;
bool PlayerFactory::RegisterType(std::string typeID, std::function<Player* ()> pCreator)
{
	auto it = m_creators.find(typeID);

	if (it != m_creators.end())
	{
		return false;
	}
	m_creators[typeID] = pCreator;
}
Player* PlayerFactory::Create(std::string typeID)
{
	auto it = m_creators.find(typeID);
	if (it == m_creators.end())
	{
		return NULL;
	}
	return it->second();
}