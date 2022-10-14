#pragma once
#include "Skill/Skill.h"
#include "cocos2d.h"

class SkillFactory
{
public:
	static SkillFactory* GetInstance() { return s_Instance = (s_Instance != nullptr) ? s_Instance : new SkillFactory(); }
	bool RegisterType(std::string typeID, std::function<Skill* ()> pCreator);
	Skill* Create(std::string typeID);
private:
	SkillFactory() {};
	std::map<std::string, std::function<Skill*()>> m_creators;
	static SkillFactory* s_Instance;
};

template<class Type>
class SkillRegister
{
public:
	SkillRegister(std::string className)
	{
		SkillFactory::GetInstance()->RegisterType(className, []()->Skill* {return new Type(); });
	};
};
