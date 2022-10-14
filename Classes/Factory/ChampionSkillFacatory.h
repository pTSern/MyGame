#pragma once
#include "ChampionSkill/ChampionSkill.h"
#include "cocos2d.h"

class ChampionSkillFactory
{
public:
	static ChampionSkillFactory* GetInstance() { return s_Instance = (s_Instance != nullptr) ? s_Instance : new ChampionSkillFactory(); }
	bool RegisterType(std::string typeID, std::function<ChampionSkill* (Champion* pOwner, PlayerStatics* pPlayerStatics)> pCreator);
	ChampionSkill* Create(std::string typeID, Champion* pOwner, PlayerStatics* pPlayerStatics);
private:
	ChampionSkillFactory() {};
	std::map<std::string, std::function<ChampionSkill* (Champion* pOwner, PlayerStatics* pPlayerStatics)>> m_creators;
	static ChampionSkillFactory* s_Instance;
};

template<class Type>
class ChampionSkillRegister
{
public:
	ChampionSkillRegister(std::string className)
	{
		ChampionSkillFactory::GetInstance()->RegisterType(className, [](Champion* pOwner, PlayerStatics* pPlayerStatics)->ChampionSkill* {return new Type(pOwner, pPlayerStatics); });
	};
};
