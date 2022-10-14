#include "Bot_Factory.h"
BotFactory* BotFactory::sp_pInstance = nullptr;
bool BotFactory::RegisterType(std::string typeID, std::function<AI* ()> pCreator)
{
	auto it = m_creators.find(typeID);

	if (it != m_creators.end())
	{
		return false;
	}
	m_creators[typeID] = pCreator;
}
AI* BotFactory::Create(std::string typeID)
{
	auto it = m_creators.find(typeID);
	if (it == m_creators.end())
	{
		return NULL;
	}
	return it->second();
}