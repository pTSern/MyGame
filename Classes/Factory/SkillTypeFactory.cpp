#include "SkillTypeFactory.h"
SkillTypeFactory* SkillTypeFactory::s_Instance = nullptr;
bool SkillTypeFactory::RegisterType(std::string typeID, std::function<SkillType* ()> pCreator)
{
	auto it = m_creators.find(typeID);

	if (it != m_creators.end())
	{
		return false;
	}
	m_creators[typeID] = pCreator;
}
SkillType* SkillTypeFactory::Create(std::string typeID)
{
	auto it = m_creators.find(typeID);
	if (it == m_creators.end())
	{
		return NULL;
	}
	return it->second();
}