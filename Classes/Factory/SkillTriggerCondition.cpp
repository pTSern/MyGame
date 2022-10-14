#include "SkillTriggerCondition.h"
SkillConditionFactory* SkillConditionFactory::s_Instance = nullptr;
bool SkillConditionFactory::RegisterType(std::string typeID, std::function<TriggerCondition* ()> pCreator)
{
	auto it = m_creators.find(typeID);

	if (it != m_creators.end())
	{
		return false;
	}
	m_creators[typeID] = pCreator;
}
TriggerCondition* SkillConditionFactory::Create(std::string typeID)
{
	auto it = m_creators.find(typeID);
	if (it == m_creators.end())
	{
		return NULL;
	}
	return it->second();
}