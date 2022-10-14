#include "ChampionSkillFacatory.h"
ChampionSkillFactory* ChampionSkillFactory::s_Instance = nullptr;
bool ChampionSkillFactory::RegisterType(std::string typeID, std::function<ChampionSkill* (Champion* pOwner, PlayerStatics* pPlayerStatics)> pCreator)
{
	auto it = m_creators.find(typeID);

	if (it != m_creators.end())
	{
		return false;
	}
	m_creators[typeID] = pCreator;
}
ChampionSkill* ChampionSkillFactory::Create(std::string typeID, Champion* pOwner, PlayerStatics* pPlayerStatics)
{
	auto it = m_creators.find(typeID);
	if (it == m_creators.end())
	{
		return NULL;
	}
	return it->second(pOwner, pPlayerStatics);
}