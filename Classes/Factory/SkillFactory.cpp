#include "SkillFactory.h"
SkillFactory* SkillFactory::s_Instance = nullptr;
bool SkillFactory::RegisterType(std::string typeID, std::function<Skill* ()> pCreator)
{
	auto it = m_creators.find(typeID);

	if (it != m_creators.end())
	{
		return false;
	}
	m_creators[typeID] = pCreator;
}
Skill* SkillFactory::Create(std::string typeID)
{
	auto it = m_creators.find(typeID);
	if (it == m_creators.end())
	{
		return NULL;
	}
	return it->second();
}