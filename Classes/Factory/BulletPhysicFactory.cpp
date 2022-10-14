#include "BulletPhysicFactory.h"
BulletPhysicFactory* BulletPhysicFactory::s_Instance = nullptr;

bool BulletPhysicFactory::RegisterType(std::string typeID, std::function<BulletPhysic* ()> pCreator)
{
	auto it = m_creators.find(typeID);
	if (it != m_creators.end())
	{
		return false;
	}
	m_creators[typeID] = pCreator;
}

BulletPhysic* BulletPhysicFactory::Create(std::string typeID)
{
	auto it = m_creators.find(typeID);
	if (it == m_creators.end())
	{
		return NULL;
	}
	return it->second();
}